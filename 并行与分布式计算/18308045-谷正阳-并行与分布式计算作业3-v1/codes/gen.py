s = '''	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1,
							  x2, y2,
							  x3, y3,
							  sz1_d_2, sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1,
							  x2, y2_a_sz3_d_2,
							  x3, y3,
							  sz1_d_2, sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1,
							  x2_a_sz2_d_2, y2,
							  x3_a_sz2_d_2, y3,
							  sz1_d_2, sz2_m_sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1,
							  x2_a_sz2_d_2, y2_a_sz3_d_2,
							  x3_a_sz2_d_2, y3,
							  sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1_a_sz1_d_2,
							  x2, y2,
							  x3, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1_a_sz1_d_2,
							  x2, y2_a_sz3_d_2,
							  x3, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_d_2, sz3_m_sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1, y1_a_sz1_d_2,
							  x2_a_sz2_d_2, y2,
							  x3_a_sz2_d_2, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_d_2);
	divide_and_conquer_kernel(ans, mat1, mat2,
							  x1_a_sz3_d_2, y1_a_sz1_d_2,
							  x2_a_sz2_d_2, y2_a_sz3_d_2,
							  x3_a_sz2_d_2, y3_a_sz1_d_2,
							  sz1_m_sz1_d_2, sz2_m_sz2_d_2, sz3_m_sz3_d_2); '''
l = s.split(';')
for i in range(8):
    args = l[i].split('(', 1)[1].split(')', 1)[0].split(',')[3:]
    temp = 'para' + str(i) + '->'
    attr = ('x1',
            'y1',
            'x2',
            'y2',
            'x3',
            'y3',
            'sz1',
            'sz2',
            'sz3')
    for j in range(9):
        args[j] = args[j].replace(' ', '')
        args[j] = args[j].replace('\n', '')
        args[j] = args[j].replace('\t', '')
        print(temp + attr[j] + '=' + args[j] + ';')
