use school
select cid, avg(score), count(*), max(score), min(score)
from choices
group by cid
