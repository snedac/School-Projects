//KEY CODES
//should clean up these hard-coded key codes
const ENTER = 13
const RIGHT_ARROW = 39
const LEFT_ARROW = 37
const UP_ARROW = 38
const DOWN_ARROW = 40


function handleKeyUp(e) {
  if (e.which == ENTER) {
    getPuzzle() //treat ENTER key like you would a submit
    document.getElementById('userTextField').value = ''

  }

  e.stopPropagation()
  e.preventDefault()

}

let currPuzzle = ""

function getPuzzle() {

  let userText = document.getElementById('userTextField').value
  if (userText && userText != '') {

    let textDiv = document.getElementById("text-area")
    textDiv.innerHTML = ''
    textDiv.innerHTML = textDiv.innerHTML + `<p> ${userText}</p>`

    currPuzzle = textDiv.innerText


    let userRequestObj = {text: userText}
    let userRequestJSON = JSON.stringify(userRequestObj)
    document.getElementById('userTextField').value = ''

    let xhttp = new XMLHttpRequest()
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        //console.log("data: " + this.responseText)
        //console.log("typeof: " + typeof this.responseText)
        let responseObj = JSON.parse(this.responseText)
  
        words = []

        for(let i = 0; i < responseObj.puzzleLines.length; i++){
          let line = responseObj.puzzleLines[i].split(" ")

          for(let j = 0; j < line.length; j++){
              let puzzleLine = line[j]
              words.push({word: puzzleLine, x: 0, y: 0})
          }
        }

        updateWordPositions()
        drawCanvas()
        
      }

      else{
        drawCanvas()
      }

      let textColor = 'black'
      let pElements = textDiv.getElementsByTagName('p')
    
      for (let i = 0; i < pElements.length; i++) {
        pElements[i].style.color = textColor
      }

    }
    xhttp.open("POST", "userText") //API .open(METHOD, URL)
    xhttp.send(userRequestJSON) //API .send(BODY)
  }
}











function solvePuzzle() {

  let tolerance  = 15

  let solvedArr = []

  let sortedByY = words.slice().sort((a, b) => a.y - b.y)

  let textDiv = document.getElementById("text-area")

  textDiv.innerHTML = ''

  let track = 0

  let lowestY = 0

  if(words[0].word.length === 1 && words[1].word.length === 1 && words[2].word.length === 1){
    while(track < sortedByY.length){

      lowestY = sortedByY[track].y
    
      let sameLines = words.filter(word => word.y >= lowestY  && word.y <= (lowestY + tolerance)).slice()
    
      let sortedByX = sameLines.slice().sort((a, b) => a.x - b.x)
    
      let sortedWord = sortedByX.map(word => word.word).join('')

      solvedArr += sortedWord
    
      textDiv.innerHTML = textDiv.innerHTML + `<p> ${sortedWord}</p>`
    
      track += sameLines.length
    
    }

    sendSolvePuzzleRequest(solvedArr)
  }


  else{
    while(track < sortedByY.length){

      lowestY = sortedByY[track].y
    
      let sameLines = words.filter(word => word.y >= lowestY  && word.y <= (lowestY + tolerance)).slice()
    
      let sortedByX = sameLines.slice().sort((a, b) => a.x - b.x);
    
      let sortedWord = sortedByX.map(word => word.word).join(' ')

      solvedArr += sortedWord
    
      textDiv.innerHTML = textDiv.innerHTML + `<p> ${sortedWord}</p>`
    
      track += sameLines.length
    
    }

    sendSolvePuzzleRequest(solvedArr)
  }


}


function  sendSolvePuzzleRequest(solvedArr){
  let userRequestObj = { textArr: solvedArr, puzzle: currPuzzle };
  let userRequestJSON = JSON.stringify(userRequestObj)

  let xhttp = new XMLHttpRequest()
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      let colour = JSON.parse(this.responseText)
      updateTextColor(colour)
    }
  }
  xhttp.open("POST", "solvePuzzle")
  xhttp.send(userRequestJSON)
}


function  updateTextColor(colour) {
  let textDiv = document.getElementById("text-area")
  if(colour == "Green"){
    let textColor = 'green'
    let pElements = textDiv.getElementsByTagName('p')
  
    for (let i = 0; i < pElements.length; i++) {
      pElements[i].style.color = textColor
    }
  }
  else{
    let textColor = 'red'
    let pElements = textDiv.getElementsByTagName('p')
  
    for (let i = 0; i < pElements.length; i++) {
      pElements[i].style.color = textColor
    }
  }

}