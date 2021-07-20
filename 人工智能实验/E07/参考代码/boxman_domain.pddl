(define (domain boxman)
  (:requirements :strips :typing:equality
                 :universal-preconditions
                 :conditional-effects)
  (:types physob loc)
  (:predicates
      (blank ?p - loc) # 位置p是否是空白格子，也即是能走的格子
      (pearl ?p - loc) # p是否是箱子应该在的位置
      (man ?p - loc) # 当前角色是否在p
      (box ?p - loc) # 箱子是否在p位置
      (at ?b - physob ?p - loc) # b物体是否在p位置
      (onpearl ?b - physob) # b是否是在终点位置上
      (line ?p0 ?p1 ?p2 -loc) #p0 p1 p2是否是联通的
      (adjacent ?p1 ?p2 -loc) # p1 p2是否是相邻的
      )   


	(:action move
                    # 填写相关代码（人物不推箱子移动的代码）
	 )

	(:action push
                    # 填写相关代码 （人物推箱子移动代码）
	  )
)