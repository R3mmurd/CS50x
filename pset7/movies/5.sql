/*
Query to list the titles and release years of all Harry Potter movies,
in chronological orders.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year
