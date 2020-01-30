var express = require("express");
var app = express();
var serv = require('http').Server(app);
var bodyParser = require("body-parser");
var fs = require('fs');
var exec = require('child_process').exec; //for running an executable

//using body parser, session
//client resources/scripts

app.use('/client/img', express.static(__dirname + '/client'));
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

/*
before login
*/

app.get('/', function(req, res){
  res.sendFile(__dirname + "/client/search.html");
});

app.get('/style.css', function(req, res){
  res.sendFile(__dirname + "/client/style.css");
});

app.get('/results', function(req, res){
  res.sendFile(__dirname + "/client/results.html");
});

//write search query to file
app.post('/search', function(req, res){
  var terms = req.body.terms;

  fs.writeFile('input', terms, function(err){
    if(err) {
      console.log('some error occured ' + err);
      return;
    }
    console.log("search terms: " + terms);
    res.send({});
  });

});

//read output from pagerank, send to user
app.get('/searchresult', function(req, res){

  var script = 'module load mpi/openmpi3-x86_64\nmake\nmpiexec -n 2 ./roogle ';

  fs.readFile('input', function(err, data){

    script += data;

    fs.writeFile("run.sh", script, function(werr){

      exec('./run.sh', function(error, stdout, stderr){
        if(error){
          console.log(error);
          return;
        }
        console.log(stdout);
        console.log(stderr);

        var contents = stdout;

        console.log('\n\n');
        var resultArr = contents.split("+++");
        var allpapers = parser.formatSearchResult(resultArr);

        var i;
        for(i = 0; i < allpapers.length; i++){
          console.log(allpapers[i]);
          console.log('\n\n');
        }

        res.send(allpapers);

      });

    });

  });

});

var parser = {

  formatSearchResult: function(result){

    var i, l = result.length;

    var allpapers = [];

    for(i = 0; i < l; i++){

      var currpaper = {};
      var split = result[i].split('\n');
      console.log(split);

      if(i > 0){
        currpaper.title = split[1];
        currpaper.authors = split[2];
        currpaper.abstract = split[3];
        currpaper.scores = split[4];
      } else {
        currpaper.title = split[1];
        currpaper.authors = split[2];
        currpaper.abstract = split[3];
        currpaper.scores = split[4];
      }

      allpapers.push(currpaper);
    }

    console.log(allpapers);

    return allpapers;

  }

};


serv.listen(8080);
console.log('program is running, go to http://localhost:8080 to test it');
