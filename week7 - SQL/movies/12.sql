-- 12: List the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
SELECT
	m.title
FROM       movies  AS m
INNER JOIN stars   AS s ON m.id = s.movie_id
INNER JOIN people  AS p ON p.id = s.person_id
WHERE
	p.name = 'Johnny Depp' OR
	p.name = 'Helena Bonham Carter'
GROUP BY
	m.id,
	m.title
HAVING
	COUNT(m.id) = 2
-- 6 titles
