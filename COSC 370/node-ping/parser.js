
module.exports.parseEcho = function(type,code) {
  var ECHOMessageType = [‘REPLY’, ‘NA’, ‘NA’, ‘DESTINATION_UNREACHABLE’,’SOURCE_QUENCH’,’REDIRECT’]; //etc
  var DestinationUnreachableCode = [‘NET’,’HOST’,’PROTOCOL’,’PORT’,’FRAGMENTATION’,’ROUTE_FAILED’,’NET_UNKNOWN’,’HOST_UNKNOWN’,’HOST_ISOLATED’,’NET_PROHIBITED’,’HOST_PROHIBITED’,’NET_UNREACHABLE’,’HOST_UNREACHABLE’,’COMM_PROHIBITED’,’HOST_PRECEDENCE’,’PRECEDENCE_CUTOFF’];
  var RedirectCode = [‘NETWORK’,’HOST’,’SERVICE_NETWORK’,’HOST_NETWORK’];
  var t = ‘OTHER’;
  var c = ‘NO_CODE’;
  if(type < ECHOMessageType.length) {
    t = ECHOMessageType[type];
  }
  switch (type) {
    case 3: c = DestinationUnreachableCode[code]; break; //DESTINATION_UNREACHABLE
    case 5: c = RedirectCode[code]; break; //REDIRECT
  }
  return Object.freeze({
    result: (type == 0),
    type: t,
    code: c
  });
}

module.exports.echo = function(source) {
  return new Promise(function(resolve, reject){
    var raw = require (“raw-socket”);
    var parser = require(‘./parser’);
    //[type]x1, [code]x1, [chksum]x2, [id]x2, [seq]x2, [data]x4
    var header = Buffer.alloc(12);
    header.writeUInt8(0x8, 0); //type
    header.writeUInt16LE(process.pid, 4); //id
    header.writeUInt16LE(checksum(header), 2);
    var socket = raw.createSocket({
      protocol: raw.Protocol.ICMP
    });
    socket.send(header, 0, 12, source, function(err, bytes) {
      if (err) {
        reject(err.toString());
      }
    });
    socket.on(“message”, function (buffer, source) {
      //[type]x1, [code]x1, [chksum]x2, [id]x2, [seq]x2, [data]x4
      // offset = 20
      var offset = 20;
      var type = buffer.readUInt8(offset);
      var code = buffer.readUInt8(offset+1);
      socket.close();
      resolve(parser.parseEcho(type,code));
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
  });
}
