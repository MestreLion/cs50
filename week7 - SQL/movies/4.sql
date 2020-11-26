-- 04: Determine the number of movies with an IMDb rating of 10.0.
SELECT
	COUNT(m.id)
FROM      movies  AS m
LEFT JOIN ratings AS r ON m.id = r.movie_id
WHERE
	r.rating = 10
-- 12
