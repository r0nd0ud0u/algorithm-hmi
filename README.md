# algorithm-hmi

Hmi to test different pathfinders algorithm:
- flood fill
- voronoi
- Dijkstra

There are 2 modes: work and edit.

<img width="800" height="628" alt="image" src="https://github.com/user-attachments/assets/2499ecb6-1210-45f5-91b7-755eb7aea070" />

 ## Edit mode

- You can modify the width and the height of your algorithm workspace.
- You can add/remove black square by left clicking the squares on the grid.
  Those squares represent obstacles as input for the algorithm.

 ## Work mode

 - You can choose your algorithm.
 - You can start your path:
    1. Left-click on the square: turns GREEN, that is your start your path
    2. Left-click on another square: turns RED, that is your path.
    => a path in YELLOW is appearing for Dijkstra algo
    => an ORANGE filling is appearing for flood-fill
    => a YELLOW filling is appearing for voronoi-fill

### Dijkstra

<img width="798" height="627" alt="image" src="https://github.com/user-attachments/assets/ef7572d2-63ea-4005-b953-7deb1d2ee25d" />

You can observe numbers of each square, only for Dijkstra algorithm. Those are random pounds. (cannot be edited at the moment)

### Voronoi fill

<img width="799" height="627" alt="image" src="https://github.com/user-attachments/assets/5ee8f468-0da7-41b0-955b-1e70f48ee612" />

### Flood fill

<img width="803" height="633" alt="image" src="https://github.com/user-attachments/assets/ce6c3167-7d9b-4b57-b706-bf0b9b2ef596" />

# Contribution

add sonar token in repository settings
