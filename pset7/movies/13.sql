/*
Query to list the names of all people who starred in a movie in which
Kevin Bacon also starred.

Author: Alejandro Mujica (aledrums@gmail.com)
*/
SELECT DISTINCT(people.name)
FROM people
INNER JOIN stars ON stars.person_id = people.id
WHERE (people.name <> 'Kevin Bacon' OR people.birth <> 1958)
AND stars.movie_id IN (
    SELECT stars.movie_id
    FROM stars
    INNER JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Kevin Bacon' and people.birth = 1958
)

