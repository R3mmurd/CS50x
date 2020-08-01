/*
Query to list the names of all people who starred in a movie released
in 2004, ordered by birth year.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
SELECT name
FROM people
WHERE id IN (
    SELECT DISTINCT stars.person_id
    FROM stars
    INNER JOIN movies ON movies.id = stars.movie_id
    WHERE movies.year = 2004
)
ORDER BY birth
