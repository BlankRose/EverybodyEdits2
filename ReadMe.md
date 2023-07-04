<h1 align='center'><b> 🙃 Everybody Edits 2 🏜 </b></h1>

<p align="center">
	<img alt="Top Language" src="https://img.shields.io/static/v1?label=Language&message=CPP&color=orange&style=plastic"/>
	<img alt="Supported" src="https://img.shields.io/static/v1?label=Supported+OS&message=Windows+/+Linux+/+OSX&color=yellow&style=plastic"/>
	<img alt="Code Size" src="https://img.shields.io/github/languages/code-size/BlankRose/everybodyedits2?label=Code+Size&color=informational&style=plastic"/>
	<img alt="Last Commit" src="https://img.shields.io/github/last-commit/BlankRose/everybodyedits2?label=Last+Commit&color=critical&style=plastic"/>
</p>

Everybody Edits is originally a Flash game, where the limits is only bounds to the players' creativity.

This project will be an attempt of its sequel, after it has been shutdown upon the
[end of Abode's support for Flash](https://www.adobe.com/products/flashplayer/end-of-life.html),
but will be remade for a better availability and cross-plateform, using CPP as its base language,
with [SMFL](https://www.sfml-dev.org/) for graphics and [Nholomann's JSON](https://github.com/nlohmann/json)
for configurations which are also cross-plateforms.

__Note:__ *Most of the assets currently used comes from the original game, so the credits goes to their original creators!*

__Link to Original Game:__ https://everybodyedits.com/

--------------------

# Showcases

![exemple_img](docs/Alpha-0.6.png)
Version: 0.6

--------------------

# Compilation

Before compiling the project, you will need two libraries, there are listed below with the versions used and tested:
 - `SFML`: Graphic library (2.6.0) (https://www.sfml-dev.org/)
 - `Nholomann JSON`: Utility library (3.11.2) (https://github.com/nlohmann/json) - INCLUDED

The project is using Makefiles to compile, it also includes a Makefile with the following rules to simplify steps:
 - `all`: Compile the project into a binary (DEFAULT_GOAL)
 - `clean`: Clear all objects files created during compilation
 - `fullclean`: Clear all objects files AND remove the final executable aswell
 - `remake`: Rebuild from scratch the project (Equivalent: `make fullclean all`)
 - `run`: Execute the binary, compiling it before hand if necessary
 - `run-leak`: Execute with leak-sanitizer, compiling aswell if necessary
 - `debug`: Displays all targetted files and dependacies by the projects
