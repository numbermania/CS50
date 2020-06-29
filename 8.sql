-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.
-- Executing 8.sql results in a table with 1 column and 4 rows.

-- SELECT name
-- FROM people p
-- JOIN stars s ON s.person_id = p.id
-- JOIN movies m ON s.movie_id = m.id
-- WHERE m.title = 'Toy Story';

SELECT name
FROM people
WHERE id IN
    (SELECT person_id FROM stars WHERE movie_id IN
        (SELECT id FROM movies WHERE title = 'Toy Story'));