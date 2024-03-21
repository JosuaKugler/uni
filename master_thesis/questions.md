# Questions

## What is an almost contact structure?
see Geiges, p. 64, Rmk 2.4.7
almost contact structure is a cooriented hyperplane field eta with a complex bundle structure J and a oriented line-bundle complementary to eta that defines the coorientation
The difference to a contact structure is: The contact structure doesn't just need a bundle structure on eta, it needs an associated form alpha that fulfills the contact condition.
However it has been showed that every almost contact manifold is actually (overtwisted) contact (see [Agustin's slides](./papers/Moreno24_slides.pdf))

### What is a bundle metric?
Let E -> M a bundle. A bundle metric is a bundle map from the fibre product of E with itself to M x \R
s.t. the reduction to each fibre is a nondegenerate bilinear form.
The fibre product is very similar to the product, only that the product maps need to fit with the two base maps that are given in the fiber product.
Why is the fibre product of something with itself not itself again? Can't I just take the identity map? No, because it needs to commute with both sides.


### What is a principal (G-)bundle?
A fiber bundle with a continuous right G-action s.t. the action preserves fibers and acts transitively and freely.

### What are transition maps in this context?
Continuous maps of the form t_ij: U_i \cap U_j -> G. They are meant in the sence that they induce a classical transition map
phi_i phi_j^{-1}: (U_i \cap U_j) x F -> (U_i \cap U_j) x F, (x, xi) \mapsto (x, t_ij(x)xi).
As G acts transitively on the fiber, all transitions can be expressed like this.

### What does reduction of structure group mean?
Example: If a manifold is oriented, that corresponds to a reduction of the structure group to GL^+(n,R) because all frames can be chosen to be oriented now.
Analogously, the choice of a volume form corresponds to a reduction of the structure group to SL(n,R).
I think the point is that there exist local trivializations s.t. all transition functions can be written as elements of the smaller group.
[Wikipedia](https://en.wikipedia.org/wiki/G-structure_on_a_manifold#Reduction_of_the_structure_group) says: A G-bundle can be reduced if and only if the transition maps can be taken to have values in H.

### A 2n-dim vector bundle with a complex structure and an arbitrary hermitian metric can locally be trivialised by n sections that are orthonormal
Locally, it's isomorphic to U x C^n. Under the isomorphism, the hermitian metric stays a hermitian metric. For any metric, we can find n orthonormal vectors.
Because U x C^n is a product space, we can just use these vectors and take them as sections.


### What does reduction of structure group to U(n)x 1 mean?
(see [Agustin's slides](./papers/Moreno24_slides.pdf))
As of now, my understanding is:
The 1 part of the structure group preserves the line bundle part. We can always choose a frame in such a way that the last vector spans the line bundle in the correct direction with norm 1, so that doesn't need to change.
The U(n) part transforms different frames of the hyperplane into each other. Using the complex structure on it, we can choose the frames in such a way that transformations are always unitary.

## Why does the definition of weak filling make sense?
What does it mean for a symplectic form to be restricted to a contact structure?
A symplectic form on a mfd associates a skew-symmetric bilinear form to every point of the manifold. The contact structure on the boundary manifold associates a plane to every point. Therefore, at each point we have to consider the restriction of the form to the 2-d subvectorspace of the 4-d tangent space.
