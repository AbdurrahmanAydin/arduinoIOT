var express=require('express');
var app=express();
var server=require('http').createServer(app);
var io=require('socket.io').listen(server);

server.listen(process.env.PORT || 3000);
console.log('Server running...');

app.get('/', function(req,res){
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){
  /* bağlantı sağlandığıda yapılacak işlemler */
  console.log('Bağlantı başarılı..');

  //Bağlantı kapandığında yapılacak işlemler burada yazılır
  socket.on('disconnect', function (data) {
    console.log('Bağlantı kesildi...');
  });

  //send fonksiyonunda arduinoya göndermek istediğimiz veriyi soketle gönderiyoruz
  socket.on('send', function(data){
     io.emit( 'status' , data ); 
     console.log(data);
  });

});