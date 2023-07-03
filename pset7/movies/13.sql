SELECT DISTINCT people.name
FROM people
INNER JOIN stars AS s1 ON s1.person_id = people.id
INNER JOIN movies AS m1 ON m1.id = s1.movie_id
INNER JOIN stars AS s2 ON s2.movie_id = m1.id
INNER JOIN people AS p2 ON p2.id = s2.person_id
WHERE p2.name = 'Kevin Bacon'
  AND p2.birth = 1958
  AND people.name <> 'Kevin Bacon';