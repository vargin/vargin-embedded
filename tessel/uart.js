var tessel = require('tessel');
var led1 = tessel.led[0].output(0);
var led2 = tessel.led[1].output(0);
var i = 0;

// baudrate must match the baudrate set in the Arduino file
var uartBridge = tessel.port['A'].UART({baudrate: 9600});

uartBridge.on('data', function(data) {
  console.log('Received data %s', data[0]);
  led1.toggle();
  led2.toggle();

  setTimeout(function() {
    led1.toggle();
    led2.toggle();
  }, 100);
});

// every 3 seconds write some data over to the arduino
setInterval(function(){
  console.log('writing ', "Hello " + i);
  uartBridge.write("Hello " + i);
  i++;
}, 5000);

uartBridge.pipe(process.stdout);