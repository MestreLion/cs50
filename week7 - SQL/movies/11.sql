-- 11: List the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT
	m.title
FROM       movies  AS m
INNER JOIN ratings AS r ON m.id = r.movie_id
INNER JOIN stars   AS s ON m.id = s.movie_id
INNER JOIN people  AS p ON p.id = s.person_id
WHERE
	p.name = 'Chadwick Boseman'
ORDER BY
	r.rating DESC
LIMIT
	5
-- 5 titles, by definition
