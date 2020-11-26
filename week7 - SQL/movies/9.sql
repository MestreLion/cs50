-- 09: list the names of all people who starred in a movie released in 2004, ordered by birth year.
SELECT
	p.name
FROM       movies AS m
INNER JOIN stars  AS s ON m.id = s.movie_id
INNER JOIN people AS p ON p.id = s.person_id
WHERE
	m.year = 2004
GROUP BY
	p.id,
	p.name
ORDER BY
	p.birth
-- | wc -l
-- 18013 rows
