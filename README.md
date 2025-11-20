# so_long
42 School mini video-game project in C

## Parsing
- first checks
    - [ ] correct number of args
    - [ ] map is in *.ber* format
    - [ ] map file is readable / openable
- read map into a linked list of lines
- converts the character map to a numeric map ; track wether or not at least 1 start, 1 exit, 1 collectible ; keep count of how much collectibles ; check whether the map is properly rectangular ; check wether the map is properly surrounded by walls
- Flood fill to check if 1) we find the exit and 2) the count of collectibles is the same is the total count we found

## Graphics

# Questions
- [ ] how to properly handle errors accross the whole project?
    - [ ] specifically, how to handle malloc fails?
