-- 08: List the names of all people who starred in Toy Story.
SELECT
	p.name
FROM       movies AS m
INNER JOIN stars  AS s ON m.id = s.movie_id
INNER JOIN people AS p ON p.id = s.person_id
WHERE
	m.title = 'Toy Story'
-- 4 people
