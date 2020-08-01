/*
Query to list the titles of all movies in which both Johnny Depp and
Helena Bonham Carter starred.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
SELECT movies.title
FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON people.id = stars.person_id
WHERE people.name = 'Johnny Depp'
INTERSECT
SELECT movies.title
FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON people.id = stars.person_id
WHERE people.name = 'Helena Bonham Carter'
