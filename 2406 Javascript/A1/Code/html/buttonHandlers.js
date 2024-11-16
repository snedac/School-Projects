//KEY CODES
//should clean up these hard coded key codes
const ENTER = 13
const RIGHT_ARROW = 39
const LEFT_ARROW = 37
const UP_ARROW = 38
const DOWN_ARROW = 40

let transposeCount = 0 //keeps track of how many times we transpose up or down


function handleKeyDown(e) {

  //console.log("keydown code = " + e.which );
  let keyCode = e.which
  if (keyCode == UP_ARROW | keyCode == DOWN_ARROW) {
    //prevent browser from using these with text input drop downs
    e.stopPropagation()
    e.preventDefault()
  }

}

function handleKeyUp(e) {
  //console.log("key UP: " + e.which);
  if (e.which == RIGHT_ARROW | e.which == LEFT_ARROW | e.which == UP_ARROW | e.which == DOWN_ARROW) {
    //do nothing for now
  }

  if (e.which == ENTER) {
    handleSubmitButton() //treat ENTER key like you would a submit

    document.getElementById('userTextField').value = ''
  }

  e.stopPropagation()
  e.preventDefault()

}

function handleSubmitButton() {
  //USES older-style XMLHttpRequest which we will replacde later with fetch()
  //get text from user text input field

  let userText = document.getElementById('userTextField').value
  //clear lines of text in textDiv
  let textDiv = document.getElementById("text-area")
  textDiv.innerHTML = ''

  if (userText && userText !== '') {
    let userRequestObj = {
      text: userText
    }
    let userRequestJSON = JSON.stringify(userRequestObj)
    //clear the user text field
    document.getElementById('userTextField').value = ''

    let xhttp = new XMLHttpRequest()
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
       console.log("typeof: " + typeof this.responseText)
       console.log("data: " + this.responseText)
       //we are expecting the response text to be a JSON string
       let responseObj = JSON.parse(this.responseText)

        words = [] //clear drag-able words array;
        if (responseObj.songLines) {
          song.songLines = responseObj.songLines
          transposedByNSemitones = 0 //reset transpose to no-transpose
          parseChordProFormat(song.songLines)
        }

      }
    }
    xhttp.open("POST", "song") //API .open(METHOD, URL)
    xhttp.send(userRequestJSON) //API .send(BODY)

  }
}

function transpose_up(){
  const transposeValue = 1
  const allChords = document.querySelectorAll('.chord')

  let scale = ""
  let note = ""

  allChords.forEach((chord) => { //goes through every chord in the chords class

    let hasMinOrsus = false

    const currentChord = chord.textContent

    for(let i = 0; i < currentChord.length; i++){ //loops through every character checking for an min or sus 
      const notes = ["A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"];

      if(notes.indexOf(currentChord[i] === -1)){ //if it has min or sus split the scale and the note into two
        scale = getScale(currentChord)
        note = getNote(currentChord)
  
        let transposedChord = transposeChord(note, transposeValue)
        chord.textContent = transposedChord + scale

        hasMinOrsus = true
        break;
      }

    }

    if(!hasMinOrsus){ //else just replace the note with the transposed one
      let transposedChord = transposeChord(currentChord, transposeValue)
      chord.textContent = transposedChord
    }
    
  });

  transposeCount++

  if (transposeCount === 12) {//checking if we need the colour to be red or green
    transposeCount = 0
    originalChords()
  } 
  else {
    changeChordColours()
  }
}



function transpose_down(){ //same as transpose up just setting transpose value to -1 instead of +1 and interating the transpose count down
  const transposeValue = -1
  const allChords = document.querySelectorAll('.chord')

  let scale = ""
  let note = ""
  

  allChords.forEach((chord) => {

    let hasMinOrsus = false

    const currentChord = chord.textContent

    for(let i = 0; i < currentChord.length; i++){
      const notes = ["A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"];

      if(notes.indexOf(currentChord[i] === -1)){
        scale = getScale(currentChord)
        note = getNote(currentChord)
  
        let transposedChord = transposeChord(note, transposeValue)
        chord.textContent = transposedChord + scale

        hasMinOrsus = true
        break;
      }

    }
    if(!hasMinOrsus){
      let transposedChord = transposeChord(currentChord, transposeValue)
      chord.textContent = transposedChord
    }
    
  });

  transposeCount--

  if (transposeCount === 0) {
    transposeCount = 12
    originalChords()
  } 
  else {
    changeChordColours()
  }

}



function transposeChord(currentChord, transposeValue){ //finds the chord we are transposing too
  const notes = ["A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"];

  let index = notes.indexOf(currentChord);

  index = (index + transposeValue) % notes.length

  if(index < 0){
    index += notes.length
    return notes[index]
  }
  else{
    return notes[index]
  }
}



function getScale(currentChord){//splits the scale with the chord holding it in a different variable
  let scale = ""
  for(let i = 0; i < currentChord.length; i++){ //goes through each character waiting for one of the special characters then saving to scale
    if(currentChord[i] == "m" || currentChord[i] == "s" || currentChord[i] == "7"){
      while(i < currentChord.length){
        scale += currentChord[i]
        i++
      }
    }
  }
  return scale
}

function getNote(currentChord){ //splits the scale with the chord holding the chord in the note variable
  let note = ""
  for(let i = 0; i < currentChord.length; i++){
    if(currentChord[i] == "m" || currentChord[i] == "s" || currentChord[i] == "7"){ //same as getScale but breaks once the special characters start
      break;
    }
    else{
      note += currentChord[i]
    }
  }
  return note
}


function changeChordColours() { //changes to red
  const allChords = document.querySelectorAll('.chord');
  allChords.forEach((chord) => {
    chord.style.color = 'red'
  });
}

function originalChords() { //resets colour to green
  const allChords = document.querySelectorAll('.chord');
  allChords.forEach((chord) => {
    chord.style.color = 'green'
  });
}