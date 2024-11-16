//connect to server and retain the socket
//connect to same host that served the document

//const socket = io('http://' + window.document.location.host)
const socket = io() //by default connects to same server that served the page
let connect = 0
let username

socket.on('serverSays', function(message, isPrivate) {
  if(connect == 1){
    let msgDiv = document.createElement('div')
    msgDiv.textContent = message
    const senderUsername = message.split(":")[0].trim()
    if(isPrivate){
      msgDiv.classList.add('private')
      document.getElementById('messages').appendChild(msgDiv)
    }
    else if(senderUsername === username){
      msgDiv.classList.add('user')
      document.getElementById('messages').appendChild(msgDiv)
    }
    else{
      msgDiv.classList.add('other')
      document.getElementById('messages').appendChild(msgDiv)
    }
  }
  if(connect == 2){
    let msgDiv = document.createElement('div')
    msgDiv.textContent = message
    msgDiv.classList.add('other')
    document.getElementById('messages').appendChild(msgDiv)
  }
})

function sendMessage() {
  if(connect == 1){
    let message = document.getElementById('msgBox').value.trim()
    if(message === '') return //do nothing

    if(message.includes(":")){
      const parts = message.split(":")
      const recipient = parts[0].trim()
      const privateMessage = parts.slice(1).join(":").trim()
      socket.emit('privateMessage', username + ": " + privateMessage, recipient)
    }
    else{
      socket.emit('clientSays', username + ": " + message)
    }
    document.getElementById('msgBox').value = ''
  }
  else{
    document.getElementById('msgBox').value = ''
  }
}

function handleKeyDown(event) {
  const ENTER_KEY = 13 //keycode for enter key
  if (event.keyCode === ENTER_KEY) {
    sendMessage()
    return false //don't propogate event
  }
}

function connectAs(){
  username = document.getElementById('msgBox').value.trim()
  let allowedValues = /^[a-zA-Z][a-zA-Z0-9]*$/

  if(allowedValues.test(username)){
    socket.emit('checkName', username, function(result){
      if(result === 1){
        document.getElementById('msgBox').value = ''
        socket.emit('clientconnect', username)
        connect = 1
      }
      else{
        connect = 2
        socket.emit('userTaken', username)
        document.getElementById('msgBox').value = ''
      }
    })
  }
  else{
    document.getElementById('msgBox').value = ''
  } 
}

function clearMessages(){
  const messagesDiv = document.getElementById('messages')
  while (messagesDiv.firstChild) {
    messagesDiv.removeChild(messagesDiv.firstChild)
  }
}


//Add event listeners
document.addEventListener('DOMContentLoaded', function() {
  //This function is called after the browser has loaded the web page

  //add listener to buttons
  document.getElementById('send_button').addEventListener('click', sendMessage)

  document.getElementById('clear_button').addEventListener('click', clearMessages)

  document.getElementById('connect_button').addEventListener('click', connectAs)

  //add keyboard handler for the document as a whole, not separate elements.
  document.addEventListener('keydown', handleKeyDown)
  //document.addEventListener('keyup', handleKeyUp)
})
