-- 12.
select c.nom, d.nom, cld.nom, r.nom, clr.nom 
from communes as c
join departements as d on d.dep = c.dep
join communes as cld on cld.com = d.cheflieu
join regions as r on r.reg = d.reg
join communes as clr on clr.com = r.cheflieu;

-- 13.
select c.nom, r.nom, count(*)
from communes as c
join departements as d on d.dep = c.dep
join regions      as r on r.reg = d.reg
group by c.nom, r.reg
having count(*) > 1
order by c.nom;

-- 14.
select sum(pop24 + pop2564 + pop65) from demographie;

-- 15.
select 1.0*sum(pop24)/sum(pop24 + pop2564 + pop65)
from demographie

-- 16.
select com, (pop24 + pop2564 + pop65 - naissances + deces)
from demographie

-- 17.
select d.com, c.nom from demographie as d
join communes as c on c.com = d.com
where naissances > (select avg(naissances) from demographie)

-- 18.
select c.* from communes c
join demographie d on d.com = c.com
where (d.pop24 + d.pop2564 + d.pop65) = 0

-- 19.
select *, (d.pop24 + d.pop2564 + d.pop65) as pop from communes c
join demographie d on d.com = c.com
where (d.pop24 + d.pop2564 + d.pop65) > 0
order by (d.pop24 + d.pop2564 + d.pop65)
limit 20

-- 20.
select c.*, (d.pop24 + d.pop2564 + d.pop65) as pop 
from communes c 
join demographie d on d.com = c.com
where pop = length(c.nom)

-- 21.
-- réponse: 9 communes
select dp.dep, dp.nom
from communes c 
join demographie dm on dm.com = c.com
join departements dp on dp.dep = c.dep 
group by dp.dep 
having (min(dm.naissances) != 0 and min(dm.deces) != 0) 
-- !! N'inclut pas Mayotte

-- 22.
select c.nom, (dm.pop24 + dm.pop2564 + dm.pop65) as pop, dp.nom, 
	chl_com.nom, (chl_dm.pop24 + chl_dm.pop2564 + chl_dm.pop65) as chl_pop
from communes c 
join demographie dm on dm.com = c.com
join departements dp on dp.dep = c.dep 
join communes chl_com on dp.cheflieu = chl_com.com
join demographie chl_dm on dp.cheflieu = chl_dm.com
where pop > chl_pop

-- 23. 
select sum(boulangeries) from equipements
--> 48568

-- 24.
select avg(pharmacies) from equipements
--> 0.699370889333715

-- 25. 
select count(*) from equipements
where poissonneries > creches
--> 572

-- 26.
select c.nom, (d.pop24 + d.pop2564 + d.pop65) as pop, e.boulangeries, 
	(1.0 * (d.pop24 + d.pop2564 + d.pop65) / e.boulangeries) as proportion
from communes c
join equipements e on e.com = c.com
join demographie d on d.com = c.com
where (pop is not NULL) and (pop > 0) and (e.boulangeries > 0)
order by proportion
limit 1
--> Le Mont-Saint-Michel: 15 hab / boulangerie

-- 27.
select c.nom, count(*)
from communes c 
group by c.nom
having count(*) >= 2
order by count(*) desc, c.nom
/*
Sainte-Colombe	12
Saint-Sauveur	11
Saint-Aubin	10
*/

-- 28.
select r.*, sum(dm.pop24 + dm.pop2564 + dm.pop65) as pop, sum(dm.naissances), 
	sum(dm.deces)
from communes c 
join demographie dm  on dm.com = c.com
join departements dp on dp.dep = c.dep
join regions r       on r.reg  = dp.reg
group by r.reg
order by CAST(r.reg AS INTEGER) 

-- 29.
select dp.nom as departement_nom, r.nom as region_nom, 
	sum(dm.pop24 + dm.pop2564 + dm.pop65) as dp_pop
from communes c
join demographie dm on  dm.com = c.com
join departements dp on dp.dep = c.dep
join regions r on       r.reg  = dp.reg
group by dp.dep
order by dp_pop desc 
limit 1

-- 30. Donnez la table des régions en y ajoutant le pourcentage entier de la 
-- population de la région habitant dans le chef-lieu de région.
select r.*, (100 * (chl_dm.pop24 + chl_dm.pop2564 + chl_dm.pop65))
	/(sum(dm.pop24 + dm.pop2564 + dm.pop65)) as pourcentage
from communes c
join demographie dm on  dm.com = c.com
join departements dp on dp.dep = c.dep
join regions r on       r.reg  = dp.reg 
join communes chl on    chl.com = r.cheflieu
join demographie chl_dm on chl_dm.com = chl.com
group by r.reg

-- 31. Donner le nombre de lycées par département. On donnera 
-- le nom et le nombre de lycées de chaque département, 
-- ordonnés par nombre de lycées décroissant puis par nom de 
-- département croissant pour l’ordre lexicographique.
select dp.nom, sum(e.lycees) as nombre_lycees
from communes c
join departements dp on dp.dep = c.dep
join equipements e   on e.com = c.com
group by dp.dep
order by nombre_lycees desc, dp.nom

-- 32. Quels sont les départements dans lesquels toutes 
-- les communes sont dotées d’au moins une pharmacie ?
select dp.*
from communes c
join departements dp on dp.dep = c.dep
join equipements e   on e.com = c.com
group by dp.dep
having e.pharmacies > 0 
/*
	13	93	13055	Bouches-du-Rhône
	15	84	15014	Cantal
	23	75	23096	Creuse
	2A	94	2A004	Corse-du-Sud
	...
	(39 total entries)
*/

-- 33. Quel est le nom de la région ayant le plus 
-- de poissonneries par habitant de plus de 65 ans ?
select r.nom, sum(e.poissonneries) as total_poissonneries, 
	sum(dm.pop65) as population_plus_de_65_ans, 
	1.0 * sum(e.poissonneries) / sum(dm.pop65) as poissonneries_par_habitant 
from communes c
join demographie dm on  dm.com = c.com
join departements dp on dp.dep = c.dep
join regions r on       r.reg  = dp.reg 
join equipements e on   e.com  = c.com
group by r.reg
having sum(e.poissonneries) > 0
order by 1.0 * sum(e.poissonneries) / sum(dm.pop65) desc
limit 1




