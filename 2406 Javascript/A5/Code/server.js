var http = require('http');
const express = require('express');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 3000;

app.set('styling', path.join(__dirname, 'styling'));
app.set('view engine', 'hbs');
app.use(express.static(path.join(__dirname, '/public')));

app.locals.pretty = true;


// Routes
app.get('/', (request, response) => {
  response.render('index', { title: 'COMP 2406', body: 'rendered with handlebars' });
});

// Start server
app.listen(PORT, (err) => {
  if (err) console.log(err);
  else {
    console.log(`Server listening on port: ${PORT} CNTL-C to Quit`);
    console.log('To Test');
    console.log('http://localhost:3000');
  }
});