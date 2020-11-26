-- 06: Determine the average rating of all movies released in 2012.
SELECT
	AVG(r.rating)
FROM      movies  AS m
LEFT JOIN ratings AS r ON m.id = r.movie_id
WHERE
	m.year = 2012
-- 6.27545924967655
