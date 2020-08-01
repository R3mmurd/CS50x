/*
Query to determine the average rating of all movies released in 2012.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
SELECT AVG(rating)
FROM ratings
INNER JOIN movies ON ratings.movie_id = movies.id
GROUP BY movies.year
HAVING movies.year = 2012
