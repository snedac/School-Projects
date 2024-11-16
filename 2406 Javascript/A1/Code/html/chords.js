/*
These functions handle parsing the chord-pro text format
*/

function parseChordProFormat(chordProLinesArray) {
  //parse the song lines with embedded
  //chord pro chords and add them to DOM

  console.log('type of input: ' + typeof chordProLinesArray)

    //add the lines of text to html <p> elements
    let textDiv = document.getElementById("text-area")
    textDiv.innerHTML = '' //clear the html

  for (let i = 0; i < chordProLinesArray.length; i++) {
    let line = chordProLinesArray[i]
    let chords = ""
    let lyrics = ""
    let track = 0

    for(let i = 0; i < line.length;){

        if(line[i] == "["){
          chords += '<span class="chord">'
          i++
          while(line[i] != "]"){
            chords += line[i]
            i++
            if(line[i] == "]"){
              chords += '</span>'
            }           
            track++
          }
        }

        if(track != 0){
          i++
          while(track > 0 && line[i] != "[" && i < line.length){
            track--
            lyrics += line[i]
            i++
          }
        }

      else{
        lyrics += line[i]
        chords += "&nbsp"
        i++
      }

    }

    console.log(chords + "\n" + lyrics)
    textDiv.innerHTML = textDiv.innerHTML + `<p> ${chords}</p>`
    textDiv.innerHTML = textDiv.innerHTML + `<p> ${lyrics}</p>`
  }
}
