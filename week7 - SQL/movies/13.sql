-- 13: List the names of all people who starred in a movie in which Kevin Bacon also starred.
--     There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--     Kevin Bacon himself should not be included in the resulting list.
SELECT
	p.name
FROM       movies  AS m
INNER JOIN stars   AS s ON m.id = s.movie_id
INNER JOIN people  AS p ON p.id = s.person_id
WHERE
	m.id IN (
		SELECT
			s2.movie_id
		FROM       people  AS p2
		INNER JOIN stars   AS s2 ON p2.id = s2.person_id
		WHERE
			p2.name  = 'Kevin Bacon' AND
			p2.birth = 1958
	) AND NOT (
		p.name  = 'Kevin Bacon' AND
		p.birth = 1958
	)
GROUP BY
	p.id,
	p.name
-- | wc -l
-- 176 rows
