import xlrd
import os
makelist = ["module"]
#makelist = ["rk2_txb"]
colname = [name + "_value" for name in makelist]
colvalue = [[] for name in makelist]
dirs = {"module":"module", 
    #"dongle":"dongle", 
    #"ant_sw":"ant_sw", 
    #"a20pad":"pad", 
    #"amlogic1083":"pad", 
    #"infotm":"pad", 
    #"linux":"pad", 
    #"rk_default":"rk_default", 
    #"rk":"pad",
    #"lab":"lab",
    #"via":"via",
    #"rk2_zd":"rk2_zd",
    #"yfw":"yfw",
    #"rk2_zd2":"rk2_zd2",
    #"via_8375":"via_8375",
    #"thzy_901":"thzy_901",
    #"rk_FCC_default":"rk_FCC_default"
    }

total_len_bin=128

def read_xls_to_h(sheetName='Sheet1',tname='./init_data/phy_6.0_init_param.xls',total_len=total_len_bin,freq=40,sta_num=1):
    
    data=xlrd.open_workbook(tname)
    #table=data.sheet_by_name(sheetName) 
    table = data.sheets()[0] 
    col_num = table.ncols 
    #print(col_num)
    
    for i in range(col_num):
        col_tmp=table.col_values(i)
        if col_tmp[0] in colname:
            index = colname.index(col_tmp[0])
            colvalue[index] = col_tmp[1:]
	    if freq==26:
		colvalue[index][48]=1
	    elif freq==40:
		colvalue[index][48]=0
	    else:
		print('freq error !!')
		pass
            print makelist[index]
    
    for name in makelist:
        if not os.path.exists('./init_data/%s'%(name)):
            os.makedirs('./init_data/%s'%(name))
        index = makelist.index(name)
        make_h(colvalue[index], './init_data/%s/esp_init_data_%s_%d.h'%(name, name,sta_num),total_len)
        make_bin(colvalue[index], './init_data/%s/esp_init_data_%s_%d.bin'%(name, name,sta_num),total_len)

    #if not os.path.exists('configs'):
        #os.makedirs('./configs')
    #for dir_item in dirs.items():
        #os.system('cp ./%s/esp_init_data_%s.h configs/esp_init_data_%s.h'%(dir_item[1], dir_item[1], dir_item[0]))
        #os.system('cp ./%s/esp_init_data_%s.bin configs/esp_init_data_%s.bin'%(dir_item[1], dir_item[1], dir_item[0]))


def get_table(sheetName='Sheet1',tname='./init_data/phy_6.0_init_param.xls'):
    data=xlrd.open_workbook(tname)
    #table=data.sheet_by_name(sheetName) 
    table = data.sheets()[0]
    #col_num = table.ncols 
    #row_num = table.nrows
    row_num = table.nrows
    data=[]
    for i in range(1,row_num):
	row_tmp=table.row_values(i)
	#print "test : row_tmp[-1]: ",row_tmp[-1]
	for j in range(len(row_tmp)):
	    if type(row_tmp[j]) == type(1.0):
		row_tmp[j] = int(row_tmp[j])
	    #if type(row_tmp[0]) == type(1.0):
		#row_tmp[0] = int(row_tmp[0])
	data.append(row_tmp)
    return data
    
    #print(col_num)
    
    



def make_bin(v_list,filename,total_len):
    fp=file(filename,'wb')
    for i in range(len(v_list)):
	v=v_list[i]
	#if v=='0x2':
	    #print(type(v))
	if type(v)==type(u''):
	    v=int(v,16)
	    #print(i,'   ',v_list)
	elif v<0:
	    v=int(v)+256
	else:
	    v=int(v)
	    pass
	v_list[i]=v
	fp.write('%c' % v)
	
    for i in range(total_len-len(v_list)):
        v=0
        fp.write('%c' % v)
	
    #print('list',v_list)
    fp.close()
    

    
    
def make_h(v_list,filename,total_len):
    f = open(filename, "w")
    ser="static char esp_init_data[] = {"
    for i in range(len(v_list)):
	#print("test2")
	#print(i,v_list[i])
	if i==(len(v_list)-1):
	    try:
		ser+=str(int(v_list[i]))+','
	    except:
		ser+=str(v_list[i])+','
	    #if(type(v_list[i])==type('1.0')):
		#ser+=str(int(v_list[i]))+','
	    #else:
		#ser+=str(v_list[i])+','
	    #if(type(v_list[i])==type('')):
		#ser+=v_list[i]+'};'
		#print("test>>>>>>>>>>>>>>>")
	    #elif(type(v_list[i])==type('5.0') or type(v_list[i])==type('5')):
		#ser+=str(v_list[i])+'};'	
		#print("ser>>>>>>>>>>>>>>>>>",ser)
	    
	else:
	    try:
		ser+=str(int(v_list[i]))+','
	    except:
		ser+=str(v_list[i])+','	    
	    #if(type(v_list[i])==type('1.0')):
		#ser+=str(int(v_list[i]))+','
	    #else:
		#ser+=str(v_list[i])+','
	    #print("test5")
	    #print("tttttttttt",type(v_list[i]))
	    #if(type(v_list[i])==type('')):
		
		#ser+=v_list[i]+' , '
		#print("test3")
	    #elif(type(v_list[i])==type('5.0') or type(v_list[i])==type('5')):
		#ser+=str(v_list[i])+','
		#print("test6")
    #print(os.path.abspath(os.path.join(path,filename)))
    #ser+="why>>>>"
    f.write(ser)

    for i in range(total_len-len(v_list)):
        if i==(total_len-len(v_list)-1):
	    v=str(0)+'};'
	else:
	    v=str(0)+','
        f.write('%s' % v)

    f.close()
    del f    

        
    
        
    
    
    #row_0=table.row_values(0)
    #print(row_0)
    #for item in row_0:
        #print item
    
    #if('pad_value') in row_0:
        #print('yes')
    #t=raw_input('')
        
        
        
        
        
if __name__=='__main__':
    
    read_xls_to_h()
