-- 10: List the names of all people who have directed a movie that received a rating of at least 9.0.
SELECT
	p.name
FROM       movies    AS m
INNER JOIN ratings   AS r ON m.id = r.movie_id
INNER JOIN directors AS d ON m.id = d.movie_id
INNER JOIN people    AS p ON p.id = d.person_id
WHERE
	r.rating >= 9
GROUP BY
	p.id,
	p.name
-- | wc -l
-- 1841 rows
