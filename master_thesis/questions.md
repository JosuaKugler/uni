# Questions/Notes

## What is an almost contact structure?
see Geiges, p. 64, Rmk 2.4.7
An almost contact structure is a cooriented hyperplane field eta with a complex bundle structure J and a oriented line-bundle complementary to eta that defines the coorientation
The difference to a contact structure is: The contact structure doesn't just need a bundle structure on eta, it needs an associated form alpha that fulfills the contact condition.
However it has been proved that every almost contact manifold is actually (overtwisted) contact (see [Agustin's slides](./papers/Moreno24_slides.pdf))


### What does "up to homotopy" mean?
I think for hyperplane fields A and B over a mfd C it means that the maps f, g: C -> TC (actually you would need the Grassmannian) with im f = A and im g = B are homotopic.
Is that correct? technically yes, but generally you think about it as "there exists a continuous interpolation between the two"

homotopy of all the information that you have

### How does (xi, dalpha) define an almost contact structure?
technically, this is just a symplectic vector bundle over the manifold.
However, Geiges, Prop 2.4.5 tells us that the space of dalpha-compatible
complex bundle structures is non-empty and contractible.
Also, the space of trivial line bundles complementary to ξ is non-empty and
contractible. (see Prop 2.4.8.)
Idea: That the space of these objects is contractible implies that they are homotopic.
I think any map to that space will be nullhomotopic then, and in particular any two objects (as the image of maps to that space) will be homotopic.

### What is a conformal class of riemannian metric
I allow the metric to be multiplied with a positive-valued function.


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

## Why is the Bourgeois construction tight?

This is difficult, it involves holomorphic curves etc. and I'm not sure if I'll be able to cover all that in my thesis.

### What is an abstract open book?
It consists of a manifold and a map. The mapping torus glued together at the boundary with a suitable other manifold gives the manifold we want to decompose.
Using the first manifold as binding, there is a natural open book fibration using the mapping torus properties.
It provides a different viewpoint that focusses on the shape of the page and
the monodromy map.

### How does the BGMZ definition of open book fit with the Geiges definition?
Consider a closed, oriented, connected smooth manifold M^(2n+1) and an open book decomposition that we denote (B, θ), together with a defining map Φ : M -> R^2 so that each z in int(D^2) is a regular value.
Here, B subset M is a closed codimension-2 submanifold, θ : M\B -> S^1 is a fiber bundle, and Φ is such that Φ^-1(0) = B and θ = Φ/|Φ|. Let us also denote by ρ the norm |Φ|.

I think the condition that every z in int(D^2) is a regular value corresponds to the tubular neighborhood around B in M where p is just the angular coordinate (somehow).

Also, theorem 2.1 in BGMZ24 needs to fit to the proof from geiges that I wrote down. However, the details aren't clear to me.
I also can't look up which approach Bourgeois took in his paper because it's not accessible.

### Why does universal tightness follow from tightness?
"The fact that 5-dimensional Bourgeois contact structures are universally tight is a simple consequence of the fact that they are tight and that finite covers of either factor of the product again yield Bourgeois contact structures."
- Every finite cover of a torus is again a torus
- How do finite covers of abstract open books look like?
- the following should be true: covering of products is product of coverings
-> at least smoothly, it definitely is a product with a torus. Why, however, is the contact structure also given by the respective Bourgeois construction?
Even when that is clear, why does universal tightness follow from tightness of all finite coverings?

### Are branched coverings important?

## What is a Plastikstufe?

The existence of a plastikstufe implies that the contact manifold does not have a (semipositive) symplectic filling. (Thm1, Niederkrueger06)
The proof of this is difficult, as it uses holomorphic curves etc.

### What is a maximally foliated submanifold?
- (M, alpha) (2n - 1)-dim contact mfd. (e.g. n = 2 -> dim = 3)
- L submfd of dimension n (e.g. n = 2, surface)
- the kernel of alpha restricted to TL defines a possibly singular foliation
 - the kernel of alpha is the contact structure hyperplane distribution
 - restriction to TL: at every point p of L, consider the intersection of ker alpha_p with T_p L. (for n = 2 this yields the characteristic foliation)

### What does Frobenius' theorem say?
In this context, the only relevant statement really is what Niederkrüger writes in his paper.

### elliptic singular set
closed, codim 2 mfd. inside L with a tubular neighborhood D^2 x S -> L (coordinates x,y,s)
alpha restricted to TL is represented by xdy - ydx on this neighborhood
    this somehow is related to open books, at least that is how one can find an easy example in Example 1 of Niederkrueger06

### Definition: A plastikstufe with singular set S
see Niederkrueger06
in dim 5, a plastikstufe can be easily visualized (see Niederkrueger06)


## What is a (parametric) h-principle?
As customary in the h-principle type framework, a parametric h-principle yields results about leafwise structures on foliations, see e.g. [28]. (BEM15)

### h-principle
h is for homotopy
I think an h-principle says that in every homotopy class of a topological kind of objects there exists a geometric object


## What is a Milnor open book?
Given an analytic function f : (X, x) → (C, 0) vanishing at x, with an isolated singularity at x, the open book decomposition OB_f of the boundary M of (X, x) with binding L = M cap f^-1(0) and projection pi = f/|f|: M \ L -> S^1 subset C is called the Milnor open book induced by f 
(Definition 5, [Milnor open books of links of some rational surface singularities](https://arxiv.org/pdf/0912.4275.pdf))


### What is the link of a singularity?
Let (X,x) be a normal complex surface singularity embedded into (C^n,0).
The manifold M that is obtained by intersection of X with a small ball around the singularity is called the link of the singularity
Together with the induced canonical contact structure, this is the contact boundary of the singularity.


### What is an A_k-singularity?
exist local coordinates, s.t. the function can be written as
x_0^2 + x_1^2 + ... + x_n^{k+1}


### What is a Brieskorn manifold?
See Geiges 7.1
- intersection of two complex mfd., the first one being S^(2n+1)
- the second one is given as the 0-set of z^a_0 + z^a_1 + ... + z^a_n
- this is a smooth complex mfd.
- the standard contact structure on S^(2n+1) induces a c.s. on this mfd.


### What is k-ADC?
Definition 2.5 in [BGMZ24]
- exists a sequence alpha_1 >= alpha_2 >= ... of contact forms
    - what is this relation between contact forms?
- all contractible periodic orbits of alpha_i-action <= D_i are non-degenerate and have degree > k
    - what is this action?
    - D_i is a sequence that goes to infinity
    - how can an action be <= some number?

### Conclusion
Ok I feel like these concepts somewhat fit together even if I don't understand the details.
As of right now, I don't think it's necessary to get all of the details in order to understand the paper.

## What is a Liouville domain?
- source: [Ideal Liouville domains - a cool gadget](https://arxiv.org/pdf/1708.08855.pdf)
- domain = compact manifold with boundary
- Liouville domain: domain F with 1-form λ s.t.
    - ω := dλ is a symplectic form on F
    - λ induces a contact form on K := ∂F orienting K as the boundary of (F, ω). 


## What is the first Chern class?
representatives of the class are differential forms.
They are only determined up to addition with an exact form.
That's where the connection to de Rham cohomology comes from.
Is it important to fully understand that?

## What is a stabilization of an open book?
Given an open book with a Legendrian disk L in the page W s.t. \partial L is a Legendrian sphere in W, we get the stabilization by attaching a symplectic handle to W along \partial L. Then we change the monodromy by composing it with a Dehn twist.

## Why are the two descriptions of the open book in Section 5.1 equal?
In the paper [Open books for Boothby-Wang bundles, fibered Dehn twists and the mean Euler characteristic](https://arxiv.org/pdf/1211.0201),
the statement is made that OB(T^∗S^n, τ^N ) is isomorphic to Σ(N, 2, . . . , 2). This is said to be proven in [Open book decompositions for contact structures on Brieskorn manifolds](https://arxiv.org/pdf/math/0405029).

## How can we kill generators of fundamental groups with surgery?
According to \url{https://www.maths.ed.ac.uk/~v1ranick/papers/milnorsurg.pdf},
this works for all homotopy groups as long as 