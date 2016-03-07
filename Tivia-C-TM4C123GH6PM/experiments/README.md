# Tricks

## Converting ```*.wav``` to ```uint8_t``` array with Octave:

* Install [Octave](http://www.gnu.org/software/octave/download.html);
* Add two packages from Octave Forge:
    * Control (```pkg install control -forge -verbose```);
    * Signal (```pkg install control -forge -verbose```).
* Load signal package (```pkg load signal```);
* Perform the following commands:
    * Extract the samples and frequency from the ```WAV``` file:
    
        ```
        [Spls, fs] = wavread('foo.wav');
        // Alternatively, see http://de.mathworks.com/help/matlab/ref/audioread.html
        [Spls, fs, nbits] = wavread('/home/azasypkin/Downloads/pacman.wav', 'native');
        ```
    
    * Downsample it, to get it to the frequency you want (11.025 kHz):
    
        ```
        Spls = downsample(Spls, round(fs/11025));
        ```
    
    * Adjust the samples (originals are fractions between -1 and 1) to range between 0 and 15 (4-bit)
    
        ```
        Spls = round((Spls+ 1)* 7.5);
        ```
      
    * Write result to a file:
        ```
        file = fopen('foo.txt', 'w');
            
        fprintf(file, 'uint8_t foo[] = {');
            
        fprintf(file, '%d,', Spls);
            
        fprintf(file, '};\n');
            
        fclose('all');
        ```