<h1 align='center'>
	<b> Project's Technical Sheet </b><br>
	<i style='font-size:90%'> Everybody Edits 2 </i>
</h1>

The original game used to be a game running under Flash until, for security reasons,
[Adobe ended Flash support since 31st December of 2020](https://www.adobe.com/products/flashplayer/end-of-life.html).

It was running on a website (https://everybodyedits.com) and some even tried to rework to revive it,
so this project will be an attempt aswell, but with aditional contents and with a overall redesign.

------------------------------

# Section A: _General_

## A.1 Accounts & Profiles
- Each player has their own profiles
- Guest accounts available

## A.2 Playable Worlds
- They will be 2D tiled worlds
- There will be available worlds, ready to join
- They can be made by both players themself or pre-made by creators

## A.3 Availability
- Computer Application ( Window / Linux / OSX )
- Phone Application ( Android / IOS )
- Web Application ( Firefox-focused )

------------------------------

# Section B: _Accounts_

## B.1 Friendship System
- Ability to add and block other poeple
- Friends can see when online and rejoin, if possible
- Blocked players cannot messages or send friend requests

## B.2 Chat System
- Ability to send messages to other poeple and staff
- A chat bubble containing the text will appears above players
- In-game, blocked players' chat will be marked blocked along of a tiny clickable chat bubble to display if wished

## B.3 Customizable Profiles
- Contains various informations about the player such: Owned Worlds and Joins History
- Informations can shown or hidden as desired
- Players can decorate their profiles with various objects

## B.4 History of Worlds
- Ability to view recently joined worlds
- Ability to view owned worlds

## B.5 Achievements (?)
- There could be some funny achievements, that can be viewed in a given tab
- Can be used to decorate accounts
- Can unlock new blocks and faces

------------------------------

# Section C: _Worlds_

## C.1 Sandbox Style
- They can be edited and modify at its owner's will
- Tiles can be placed anywhere and everywhere across the world
- There can be owned worlds by players, which allows for more controls over the world
- There is also "open" worlds, which are temporary and not destroyed when everyone leaves

## C.2 Joins and Leaves
- Joins and leaves messages would be displayed in chat
- A list of players who are in the world can be viewed
- Owners can kick and ban players accordingly

## C.3 Permissions System
- There will a system which handles permissions, using the following ranks:
    - Visitor: Can only explore the world (default for owned worlds)
    - Builder: Can edit the world (default for "open" worlds)
    - Admin: Can kick and mutes and make players builders or not
    - Owner: Can promote players to admins for the given world and ban players
    - Game Staff: Varies (Section D)
- Permissions can be granted via an easy to use GUI or Command used in chat
- For "open" worlds, everyone has the Builder rank

## C.4 2D Tiled Design
- Worlds will be tiled over a 2 dimensional landscape, with pre-determined sizes
- Each tile has a set of scaled size ( to determine )
- Tiles can be freely edited as long as players has the rank Builder or above

------------------------------

# Section D: _Moderation_

## D.1 Set of Rules
- Probably the most important thing when it comes to online features
- There must be a well defined and detailed set of rules

## D.1 Game Staff
- There will be staff in-game, to help moderate the game
- Staff will have their own grades aswell:
    - Moderators: Can warn and mutes players and fix the problem
    - Admins: Can aswell bans players off the game
    - Developpers: Can promotes staffs accordingly

## D.2 Report System
- Ability to report players and worlds that breaks the rules
- Staff members can review the reports and apply sanctions if needed
- Report abuses must be handled properly

## D.4 Support
- There will be an external support server (maybe on Discord?)
- Players can contact staff from there and suggests features
- There will be also a email available for support

------------------------------

# Section E: _Developpement_

## E.1 General Information
- This section might change over time, during its developpement
- While Web and Phone exports are planned, they wont be primarly focused

## E.2 Software Application
- Target plateforms: Windows / Linux / OSX
- Languages used: C++ / ASM
- Libraries used: SFML

## E.3 Handheld Application
- Target plateforms: Android / IOS
- Languages used: C++ / Java
- Libraries used: (?)

## E.4 Web Application
- Target plateforms: Any Browers (Firefox Primarly)
- Languages used: WebASM / HTML / CSS / TypeScript
- Libraries used: (?)

## E.5 Server Side
- Servers will be using the same architectures as of computers (see E.2)
- This must be protected against MySQL injections, DDoS and any kind of attacks
- Database will be based upon any MySQL frameworks
