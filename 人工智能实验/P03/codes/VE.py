import itertools


class VariableElimination:
    @staticmethod
    def inference(factorList, queryVariables,
                  orderedListOfHiddenVariables, evidenceList):
        for ev in evidenceList:
            #Your code here
            for i in range(len(factorList)):
                if ev in factorList[i].varList:
                    factorList[i] = factorList[i].restrict(
                        ev, evidenceList[ev])
        for var in orderedListOfHiddenVariables:
            #Your code here
            new_factor = None
            i = 0
            while True:
                while i < len(factorList):
                    if var in factorList[i].varList:
                        if new_factor is None:
                            new_factor = factorList[i]
                        else:
                            new_factor = new_factor.multiply(factorList[i])
                        del factorList[i]
                        break
                    i += 1
                else:
                    break
            if new_factor is not None:
                factorList.append(new_factor.sumout(var))
        res = factorList[0]
        for factor in factorList[1:]:
            res = res.multiply(factor)
        total = sum(res.cpt.values())
        res.cpt = {k: v/total for k, v in res.cpt.items()}
        return res

    @staticmethod
    def printFactors(factorList):
        for factor in factorList:
            factor.printInf()

    @staticmethod
    def orderWidth(factorList, orderedListOfHiddenVariables,
                   evidenceList, len_domain):
        orderedListOfHiddenVariables = evidenceList.keys() + orderedListOfHiddenVariables
        buckets = {var: list() for var in orderedListOfHiddenVariables}
        for ev in evidenceList:
            buckets[ev].append({ev})
        for f in factorList:
            for var in orderedListOfHiddenVariables:
                if var in f.varList:
                    buckets[var].append(set(f.varList))
                    break
        num_var = len(len_domain)
        width = 0
        i = 0
        while i < len(orderedListOfHiddenVariables) and num_var > width:
            var = orderedListOfHiddenVariables[i]
            bucket = buckets[var]
            i += 1
            if len(bucket) > 0:
                new_edge = reduce(lambda x, y: x | y, bucket)
                new_edge.remove(var)
                for var in orderedListOfHiddenVariables[i:]:
                    if var in list(new_edge):
                        width = max(width, len(new_edge))
                        buckets[var].append(new_edge)
                        break
            num_var -= 1
        return width

    @staticmethod
    def sortedOrders(factorList, queryVariables, evidenceList, len_domain):
        # queryVariables = set(queryVariables)
        # hidden = filter(
        #     lambda var: var not in queryVariables and var not in evidenceList, len_domain.keys())
        # def orderWidth(order):
        #     return VariableElimination.orderWidth(
        #         factorList, list(order), evidenceList, len_domain)
        # orders = [list(order) for order in itertools.permutations(hidden)]
        # orders.sort(key=orderWidth)
        # return orders
        orders = [list(order) for order in itertools.permutations(filter(lambda var: var not in set(queryVariables) and var not in evidenceList, len_domain.keys()))]
        orders.sort(key=lambda order: VariableElimination.orderWidth(factorList, order, evidenceList, len_domain))
        return orders

    @staticmethod
    def bestOrder(factorList, queryVariables, evidenceList, len_domain):
        # queryVariables = set(queryVariables)
        # hidden = filter(
        #     lambda var: var not in queryVariables and var not in evidenceList, len_domain.keys())
        # def orderWidth(order):
        #     return VariableElimination.orderWidth(
        #         factorList, list(order), evidenceList, len_domain)
        # return list(min(itertools.permutations(hidden), key=orderWidth))
        return list(min(itertools.permutations(filter(lambda var: var not in set(queryVariables) and var not in evidenceList, len_domain.keys())), key=lambda order: VariableElimination.orderWidth(factorList, list(order), evidenceList, len_domain)))

    @staticmethod
    def minDegreeOrder(factorList, queryVariables, evidenceList, len_domain):
        queryVariables = set(queryVariables)
        hidden = filter(
            lambda var: var not in queryVariables and var not in evidenceList, len_domain.keys())
        G = {var: set() for var in hidden}
        for f in factorList:
            varList = filter(
                lambda var: var not in queryVariables and var not in evidenceList, f.varList)
            varSet = set(varList)
            for var in varList:
                G[var].update(varSet)
        order = list()
        while len(hidden) > 0:
            min_var = min(hidden, key=lambda var: len(G[var]))
            for var in hidden:
                if min_var in G[var]:
                    G[var].remove(min_var)
            order.append(min_var)
            G_min_var = G[min_var]
            hidden.remove(min_var)
            for var in list(G_min_var):
                G[var].update(G_min_var)
        return order

    @staticmethod
    def minFillOrder(factorList, queryVariables, evidenceList, len_domain):
        queryVariables = set(queryVariables)
        hidden = filter(
            lambda var: var not in queryVariables and var not in evidenceList, len_domain.keys())
        G = {var: set() for var in hidden}
        for f in factorList:
            varList = filter(
                lambda var: var not in queryVariables and var not in evidenceList, f.varList)
            varSet = set(varList)
            for var in varList:
                G[var].update(varSet)
        order = list()
        while len(hidden) > 0:
            min_var = min(hidden, key=lambda var: sum(
                (len(G[var] - G[v]) for v in list(G[var]))))
            for var in hidden:
                if min_var in G[var]:
                    G[var].remove(min_var)
            order.append(min_var)
            G_min_var = G[min_var]
            hidden.remove(min_var)
            for var in list(G_min_var):
                G[var].update(G_min_var)
        return order


class BucketElimination(VariableElimination):
    @staticmethod
    def inference(factorList, queryVariables,
                  orderedListOfHiddenVariables, evidenceList, len_domain):
        orderedListOfHiddenVariables = evidenceList.keys() + orderedListOfHiddenVariables
        buckets = {var: list() for var in orderedListOfHiddenVariables}
        query_bucket = list()
        for ev in evidenceList:
            new_var_list = [ev]
            new_node = Node("f" + str(new_var_list), new_var_list)
            new_cpt = dict()
            for i in range(len_domain[ev]):
                if i == evidenceList[ev]:
                    new_cpt[str(i)] = 1.0
                else:
                    new_cpt[str(i)] = 0.0
            new_node.setCpt(new_cpt)
            buckets[ev].append(new_node)
        for f in factorList:
            for var in orderedListOfHiddenVariables:
                if var in f.varList:
                    buckets[var].append(f)
                    break
            else:
                query_bucket.append(f)
        i = 0
        while i < len(orderedListOfHiddenVariables):
            var = orderedListOfHiddenVariables[i]
            bucket = buckets[var]
            i += 1
            if len(bucket) > 0:
                new_factor = reduce(Node.multiply, bucket)
                new_factor = new_factor.sumout(var)
                varSet = new_factor.varList
                for var in orderedListOfHiddenVariables[i:]:
                    if var in varSet:
                        buckets[var].append(new_factor)
                        break
                else:
                    query_bucket.append(new_factor)

        res = query_bucket[0]
        for factor in query_bucket[1:]:
            res = res.multiply(factor)
        total = sum(res.cpt.values())
        res.cpt = {k: v/total for k, v in res.cpt.items()}
        return res


class Util:
    @staticmethod
    def to_binary(num, len):
        return format(num, '0' + str(len) + 'b')


class Node:
    def __init__(self, name, var_list):
        self.name = name
        self.varList = var_list
        self.cpt = {}

    def setCpt(self, cpt):
        self.cpt = cpt

    def printInf(self):
        print "Name = " + self.name
        print " vars " + str(self.varList)
        for key in self.cpt:
            print "   key: " + key + " val : " + str(self.cpt[key])

    def multiply(self, factor):
        """function that multiplies with another factor"""
        #Your code here
        same_var = set()
        same_var_pos = list()
        for i in range(len(self.varList)):
            for j in range(len(factor.varList)):
                if self.varList[i] == factor.varList[j]:
                    same_var.add(self.varList[i])
                    same_var_pos.append((i, j))
                    break
        newList = self.varList[:]
        for var in factor.varList:
            if var not in same_var:
                newList.append(var)
        new_node = Node("f" + str(newList), newList)
        new_cpt = dict()
        for k1, v1 in self.cpt.items():
            for k2, v2 in factor.cpt.items():
                for i, j in same_var_pos:
                    if k1[i] != k2[j]:
                        break
                else:
                    new_k2 = list()
                    for i in range(len(k2)):
                        if factor.varList[i] not in same_var:
                            new_k2.append(k2[i])
                    new_cpt[k1 + ''.join(new_k2)] = v1 * v2
        new_node.setCpt(new_cpt)
        return new_node

    def sumout(self, variable):
        """function that sums out a variable given a factor"""
        #Your code here
        pos_x = self.varList.index(variable)
        new_var_list = self.varList[:pos_x] + self.varList[pos_x + 1:]
        new_node = Node("f" + str(new_var_list), new_var_list)
        new_cpt = dict()
        for k, v in self.cpt.items():
            new_k = k[:pos_x] + k[pos_x + 1:]
            if new_cpt.get(new_k) is None:
                new_cpt[new_k] = v
            else:
                new_cpt[new_k] += v
        new_node.setCpt(new_cpt)
        return new_node

    def restrict(self, variable, value):
        """function that restricts a variable to some value 
        in a given factor"""
        #Your code here
        pos_x = self.varList.index(variable)
        new_var_list = self.varList[:pos_x] + self.varList[pos_x + 1:]
        new_node = Node("f" + str(new_var_list), new_var_list)
        new_cpt = dict()
        for k, v in self.cpt.items():
            if k[pos_x] == str(value):
                new_cpt[k[:pos_x] + k[pos_x + 1:]] = v
        new_node.setCpt(new_cpt)
        return new_node


if __name__ == '__main__':
    import yaml
    import time


    len_domain = dict()
    domain_map = dict()
    with open('domains.yml') as f:
        table = yaml.load(f, Loader=yaml.FullLoader)
        for var_name in table:
            index = 0
            for value in table[var_name]:
                if domain_map.get(value) is None:
                    domain_map[value] = {var_name: index}
                else:
                    domain_map[value][var_name] = index
                index += 1
            len_domain[var_name] = index

    facts = list()
    with open('CPTs.yml') as f:
        table = yaml.load(f, Loader=yaml.FullLoader)
        for fact_name in table:
            fact = table[fact_name]
            facts.append(Node(fact_name, fact[0]))
            cpt = dict()
            for item in fact[1:]:
                cpt[''.join((str(domain_map[item[i]][fact[0][i]])
                             for i in range(len(item[:-1]))))] = item[-1]
            facts[-1].setCpt(cpt)

    with open('querys.yml') as f:
        file_index = 1
        method_names = ['Best Order', 'Min-Degree Order', 'Min-Fill Order']
        order_names = ['Median Order', 'Worst Order']
        methods = [VariableElimination.bestOrder,
                    VariableElimination.minDegreeOrder, VariableElimination.minFillOrder]
        for query, evidence in yaml.load(f, Loader=yaml.FullLoader):
            query = query.keys()
            evidence = {key: domain_map[value][key]
                        for key, value in evidence.items()}
            print 'Query' + str(file_index) + ':'
            order = VariableElimination.minFillOrder(
                facts, query, evidence, len_domain)
            BucketElimination.inference(
                facts[:], query, order, evidence, len_domain).printInf()
            print ''
            with open('query' + str(file_index) + '.txt', 'w+') as f:
                for i in range(3):
                    t = 0
                    for j in range(1000):
                        start = time.clock()
                        order = methods[i](facts, query, evidence, len_domain)
                        end = time.clock()
                        t += end - start
                    f.write(method_names[i] + ': ' + str(order) + '\n')
                    f.write('Width: ' + str(VariableElimination.orderWidth(facts, order, evidence, len_domain)) + '\n')
                    f.write('Time consumed: ' + str(t * 1000) + ' us\n')
                    f.write('\n')
                    f.write('\tVariableElimination:\n')
                    t = 0
                    for j in range(1000):
                        start = time.clock()
                        VariableElimination.inference(facts[:], query, order, evidence)
                        end = time.clock()
                        t += end - start
                    f.write('\tTime consumed: ' + str(t * 1000) + ' us\n')
                    f.write('\n')
                    f.write('\tBucketElimination:\n')
                    t = 0
                    for j in range(1000):
                        start = time.clock()
                        BucketElimination.inference(
                            facts[:], query, order, evidence, len_domain)
                        end = time.clock()
                        t += end - start
                    f.write('\tTime consumed: ' + str(t * 1000) + ' us\n')
                    f.write('\n')
                orders = VariableElimination.sortedOrders(facts, query, evidence, len_domain)

                order_indexes = (len(orders) / 2, -1)
                for i in (0, 1):
                    order = orders[order_indexes[i]]
                    f.write(order_names[i] + ': ' + str(order) + '\n')
                    f.write('Width: ' + str(VariableElimination.orderWidth(facts, order, evidence, len_domain)) + '\n')
                    f.write('\tVariableElimination:\n')
                    t = 0
                    for j in range(1000):
                        start = time.clock()
                        VariableElimination.inference(facts[:], query, order, evidence)
                        end = time.clock()
                        t += end - start
                    f.write('\tTime consumed: ' + str(t * 1000) + ' us\n')
                    f.write('\n')
                    f.write('\tBucketElimination:\n')
                    t = 0
                    for j in range(1000):
                        start = time.clock()
                        BucketElimination.inference(
                            facts[:], query, order, evidence, len_domain)
                        end = time.clock()
                        t += end - start
                    f.write('\tTime consumed: ' + str(t * 1000) + ' us\n')
                    f.write('\n')

                f.write('Average Order:\n')
                f.write('\tVariableElimination:\n')
                t = 0
                for order in orders:
                    for j in range(100):
                        start = time.clock()
                        VariableElimination.inference(facts[:], query, order, evidence)
                        end = time.clock()
                        t += end - start
                f.write('\tTime consumed: ' + str(t / len(orders) * 10000) + ' us\n')
                f.write('\n')
                f.write('\tBucketElimination:\n')
                t = 0
                for order in orders:
                    for j in range(100):
                        start = time.clock()
                        BucketElimination.inference(
                            facts[:], query, order, evidence, len_domain)
                        end = time.clock()
                        t += end - start
                f.write('\tTime consumed: ' + str(t / len(orders) * 10000) + ' us\n')
                f.write('\n')
            file_index += 1
