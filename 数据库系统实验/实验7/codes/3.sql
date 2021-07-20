use school
select distinct sid, score
from choices inner join courses on choices.cid = courses.cid
where cname = 'C++'
order by score
