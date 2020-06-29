-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.
-- Executing 12.sql results in a table with 1 column and 6 rows.

SELECT m.title
FROM movies m
JOIN stars s ON m.id = s.movie_id
JOIN people p ON p.id = s.person_id
WHERE m.id IN
    -- List of movies where Johnny Depp was a star
    (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = 'Johnny Depp'))
    AND p.name = 'Helena Bonham Carter';