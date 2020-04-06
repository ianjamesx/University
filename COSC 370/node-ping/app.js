var raw = require('raw-socket');
var parser = require('./parser');
//[type]x1, [code]x1, [chksum]x2, [id]x2, [seq]x2, [data]x4
var header = Buffer.alloc(12);
header.writeUInt8(0x8, 0); //type
header.writeUInt16LE(process.pid, 4); //id
header.writeUInt16LE(checksum(header), 2);

var socket = raw.createSocket({
  protocol: raw.Protocol.ICMP
});


socket.send(header, 0, 12, source, function(err, bytes){
  if(err){
    console.log(error.toString());
  }
});

socket.on('message', function (buffer, source) {
  //[type]x1, [code]x1, [chksum]x2, [id]x2, [seq]x2, [data]x4
  // offset = 20
  var offset = 20;
  var type = buffer.readUInt8(offset);
  var code = buffer.readUInt8(offset+1);
  socket.close();
});

function checksum(array) {
  var buffer = Buffer.from(array);
  var sum = 0;
  for (var i=0; i<buffer.length; i=i+2) {
    sum += buffer.readUIntLE(i, 2);
  }
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  sum = ~sum;
  //return unsigned
  return (new Uint16Array([sum]))[0];
}

self._tester = setInterval(() => {
  for (var x in self._clients) {
  var ip = self._clients[x].address;
  ping.echo(ip).then( (res)=>{
    if(!res.result){
      delete self._clients[x];
      self.emit('removed',x);
    }
  }).catch((err)=>{
    console.log(err);
  });
  }
},3000);

Network.prototype.dispose = function dispose() {
  clearInterval(this._tester);
  this._clients = {};
  this._listener.close();
}
