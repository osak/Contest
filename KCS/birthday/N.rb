#!/usr/bin/env ruby

# From AOJ
=begin
JOI = %q(
Card Game
Data Conversion
Dice
Cup
Card Game II
Questionnaire
String
Square
String With Rings
Sheets
Score
Who Are The Student Yet To Submit
Caesar Cipher
Shuffle The Cards
Quality Checking
School Road
Maximum Sum
Longest Steps
The Oldest Site
Worst Sportswriter
Lightest Mobile
Change
JOI and IOI
Card Game
Searching Constellation
Osenbei
Boat Travel
Setting Go Stones
Common Sub-String
Darts
Pyon-Pyon River Crossing
Paint Color
Time Card
Contest
Chain
Crossing Black Ice
Shuffle
Bingo
IOIOI
Pizza
Amidakuji
Walk
Authentication Level
Receipt
Sugoroku
Party
Lining up the cards
Commute routes
Reindeer with no sense of direction
A Traveler
Dividing Snacks
Icicles
Exposition
Dungeon
Total Time
Ring
Tile
A First Grader
Cheese
JOI Flag
Planetary Exploration
Books
Shopping in JOI Kingdom
Walking Santa
Bug Party
Lunch
Soccer
Best Pizza
Pasta
Illumination
Zig-Zag Numbers
JJOOII
Card Game is Fun
Night Market
Nails
Festivals in JOI Kingdom
Homework
Unique number
Signboard
Hot days
Fish
Gifts
Triangle Types
Common Divisors
Two Number Cards
Nearest Two Points
Palindrome
Tunnel
Simple Calculator
Production
Available Areas
Beads
Average Score
Vote
Super Metropolis
Schedule
Taxis
Xiao Long Bao
).each_line.map(&:chomp)
=end

# From wcipeg.com, ioinformatics.com
IOI = %q(
The Buses
The Circle
Polygon
Little Shop of Flowers
Hidden Codes
Underground City
Traffic Lights
Flatten
A Strip of Land
Palindrome
Car Parking
Mesian Strength
Walls
Post Office
Building with Blocks
Score
Double Crypt
Depot
The Troublesome Frog
Utopia Divided
XOR
Batch Scheduling
Bus Terminals
Two Rods
Trail Maintenance
Comparing Code
Reverse
Guess Which Cow
Amazing Robots
Seeing the Boundary
Hermes
Artemis
Phidias
Farmer
Empodia
Polish Flag
Garden
Mean Sequence
Mountains
Mountain
Birthday
Rectangle Game
Rivers
Forbidden Subgraph
Deciphering the Mayan Writing
A Black Box Game
Joining Points
Pyramid
Aliens
Flood
Sails
Miners
Pairs
Trainings
Training
Type Printer
Linear Garden
Archery
Hiring
Raisins
Mecho
Regions
Salesman
POI
Garage
Dreaming
Art Class
Wombats
Cave
Robots
Game
Pebbling Odometer
Parachute Rings
Crayfish Scrivener
Ideal City
Jousting Tournament
Last Supper
Tropical Garden
Race
Rice Hub
Crocodile's Underground City
Dancing Elephants
Raisins
Crocodile
Elephants
Parrots
Islands
Fish
Teleporters
Pyramid Base
The Valley of Mexico
Cluedo
Hotter Colder
Language
Memory
Quality of Living
Traffic Congestion
Maze
Save It
Saveit
Mobile Phones
Ioiwari Game
Twofive
Contact
Starry Night
Party Lamps
Picture
Camelot
A Game
Job Processing
Network of Schools
Sorting a Three-Valued Sequence
Longest Prefix
Magic Squares
Packing Rectangles
Shopping Offers
Printing
Letter Game
Street Race
Wires and Switches
The Triangle
The Castle
The Primes
The Clocks
The Toxic iShongololo
Mars Explorer
Game of Hex
Toxic iShongololo
Map Labelling
Character Recognition
Stacking Containers
).each_line.map(&:chomp)

IOI_PRACTICE = %q(
Fence Factory
Word Chains
Bar Codes
Faulty Links
Median Difference
Driving Home
Balancing Act
Numbers
Olympic Avenues
Divisor Game
Domino
Polish Flag
Area
Hill
Museum
Guess
Game Show
Fruit
Alphabets
Hottest
Valley
).each_line.map(&:chomp)

PROBLEMS = (IOI).map{|s| s.downcase}
name = gets.chomp.downcase.gsub(/\s+$/, "")
raise if name == ""
puts PROBLEMS.index(name) ? "YES" : "NO"
