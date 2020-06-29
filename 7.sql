-- In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
-- Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
-- Movies that do not have ratings should not be included in the result.
-- Executing 7.sql results in a table with 2 columns and 6,835 rows.

SELECT title, rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating IS NOT NULL
AND year = 2010
ORDER BY rating DESC, title;

-- SElECT count(*)
-- FROM movies
-- JOIN ratings ON movies.id = ratings.movie_id
-- WHERE rating IS NOT NULL
-- AND year = 2010
-- ORDER BY rating DESC, title;