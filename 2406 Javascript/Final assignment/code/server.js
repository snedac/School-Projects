/*
Basic express server with middleware, SQLite database, and Handlebars template rendering.

The server allows client to find chord progressions of songs in
its SQLite database. The database provided has chord progressions
of some 1200 popular jazz standards.

Here we use server-side templating using the Handlebars template engine to generate the HTML for the response pages to send to the client.
Handlebars is a popular templating format/engine.
Other popular ones include: PUG (formarly Jade), EJS, Liquid, Mustache.
Handlebar views are rendered from data obtained from the SQLite database.

The template engine merges data provided in the form of a javascript object
with html represented in the .hbs handlebars template files.
The combination is 'rendered' and sent to the client as .html.

This is an Express 4.x application.
Here we use a routes module. We put our route handling code in
a separate module that is required by the main app.

We use the exported route functions in the 'use' and 'get'
routes. Typically 'use' calls functions that invoke next() whereas our
get and post routes send responses to the client.

Testing: (user: ldnel password: secret)
http://localhost:3000/index.html
http://localhost:3000/users
*/

//Cntl+C to stop server

var http = require('http');
var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var bodyParser = require('body-parser');
const axios = require('axios');

var  app = express(); //create express middleware dispatcher

const PORT = process.env.PORT || 3000

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs'); //use hbs handlebars wrapper

app.locals.pretty = true; //to generate pretty view-source code in browser

//read routes modules
var routes = require('./routes/index');


//some logger middleware functions
function methodLogger(request, response, next){
		   console.log("METHOD LOGGER");
		   console.log("================================");
		   console.log("METHOD: " + request.method);
		   console.log("URL:" + request.url);
		   next(); //call next middleware registered
}
function headerLogger(request, response, next){
		   console.log("HEADER LOGGER:")
		   console.log("Headers:")
           for(k in request.headers) console.log(k);
		   next(); //call next middleware registered
}

//register middleware with dispatcher
//ORDER MATTERS HERE
//middleware
app.use('/js', express.static(path.join(__dirname, 'routes')));
app.use(routes.authenticate); //authenticate user
app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
//app.use(methodLogger);
//routes
app.get('/', routes.index);
app.get('/users', routes.users);


app.get('/main', function (request, response) {
    response.render('main', { title: 'Pokémon Data'});
});

app.get('/choice', function (request, response) {
    response.render('choice', { title: 'Game Options'});
});


var sqlite3 = require('sqlite3').verbose();
var db = new sqlite3.Database('data/db_database');
app.post('/login', function (request, response) {
    var username = request.body.username;
    var password = request.body.password;

    var authorized = false;
    // check database users table for user
    db.all("SELECT userid, password FROM users", function (err, rows) {
        for (var i = 0; i < rows.length; i++) {
            if (rows[i].userid == username && rows[i].password == password) {
                authorized = true;
                break;
            }
        }
        if (authorized) {
            // Send a success response to the client
            response.status(200).json({ message: 'Authentication successful' });
        } else {
            // Send an error response to the client
            response.status(401).json({ message: 'Authentication failed' });
        }
    });
});

app.post('/signup', function (request, response) {
    var username = request.body.username;
    var password = request.body.password;

    // Insert the new user into the database
    var sqlString = "INSERT INTO users (userid, password) VALUES (?, ?)";
    db.run(sqlString, [username, password], function (err) {
        if (!err) {
            // Signup successful
            response.status(200).json({ message: 'Signup successful' });
        } else {
            // Signup failed
            response.status(500).json({ message: 'Signup failed' });
        }
    });
});

app.get('/pokemon/:name', function(req, res) {
    var pokemonName = req.params.name;

    // Make a request to the PokeAPI
    axios.get(`https://pokeapi.co/api/v2/pokemon/${pokemonName}`)
        .then(response => {
            // Send the Pokemon data back to the client
            res.json(response.data);
        })
        .catch(error => {
            // Handle errors
            res.status(500).json({ error: 'Internal Server Error' });
        });
});

let savedGameChoice = null;

app.post('/saveGameChoice', (req, res) => {
    const { gameChoice } = req.body;
    savedGameChoice = gameChoice;

    console.log('Game choice saved on the server:', savedGameChoice);
    
    res.sendStatus(200);
});


app.get('/getSavedGameChoice', (req, res) => {
    res.json({ gameChoice: savedGameChoice });
});

//start server
app.listen(PORT, err => {
  if(err) console.log(err)
  else {
		console.log(`Server listening on port: ${PORT} CNTL:-C to stop`)
		console.log(`To Test:`)
		console.log('user: user password: pass1')
		console.log('http://localhost:3000')
		console.log('http://localhost:3000/users')
	}
})
