USE SCHOOL
SELECT SNAME
FROM STUDENTS
WHERE (SELECT SUM(SCORE)
		FROM CHOICES
		WHERE STUDENTS.SID = CHOICES.SID) > 400