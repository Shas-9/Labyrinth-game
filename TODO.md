* Create a singleton class "FontManager" and use it for all fonts (to never load the same font more than once)
* Make button text size responsive
* Move the player name property out of utility and into a better organized singleton class
* Adhere to the "loading a texture" documentation in the README
* Change the addScore function in HighscoreManager such that if a name already on the highscore lise obtained another score worthy of the highscore label, then the position of the player on the list would be changed accordingly rather than having two highscore records on the list corresponding to the same player.
* Possibly add inertia to camera movements similar to the effect simulated by the following p5js code available to view on https://editor.p5js.org/
```js
class Vector {
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }
  
  render() {
    circle(this.x, this.y, 25);
  }
  
  print() {
    console.log(this.x, this.y)
  }
}

function setup() {
  createCanvas(400, 400);
}

function getMid(vec1, vec2) {
  let res = new Vector(-(vec1.x-vec2.x)/10, -(vec1.y-vec2.y)/10);
  return new Vector(vec1.x+res.x, vec1.y+res.y);
}

const mouseCircle = new Vector(0, 0);
let follow = new Vector(0, 0);

function inertia() {
  let mid = getMid(follow, mouseCircle);
  follow.x = mid.x;
  follow.y = mid.y;
}

function draw() {
  background(220);
  mouseCircle.x = mouseX;
  mouseCircle.y = mouseY;
  
  mouseCircle.render();
  follow.render();
  
  inertia();
}
```