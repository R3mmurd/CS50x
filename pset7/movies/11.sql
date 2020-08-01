/*
Query to list the titles of the five highest rated movies (in order)
that Chadwick Boseman starred in, starting with the highest rated.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
SELECT movies.title
FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON people.id = stars.person_id
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5
