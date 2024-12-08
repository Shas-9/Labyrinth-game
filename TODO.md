* Create a singleton class "FontManager" and use it for all fonts (to never load the same font more than once)
* Make button text size responsive
* Move the player name property out of utility and into a better organized singleton class
* Adhere to the "loading a texture" documentation in the README
* Change the addScore function in HighscoreManager such that if a name already on the highscore lise obtained another score worthy of the highscore label, then the position of the player on the list would be changed accordingly rather than having two highscore records on the list corresponding to the same player.