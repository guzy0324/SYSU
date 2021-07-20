class GoodTrajectory:
    def __init__(self, obs, acts, R):
        self.obs = obs
        self.acts = acts
        self.R = R
    def __lt__(self, other):
        return self.R <= other.R
