USE SCHOOL
SELECT CHOICES.SID
FROM CHOICES, COURSES
WHERE CHOICES.CID = COURSES.CID
AND CNAME = 'ERP'
AND SCORE = (SELECT MAX(SCORE)
            FROM CHOICES, COURSES
            WHERE CHOICES.CID = COURSES.CID
            AND CNAME = 'ERP')