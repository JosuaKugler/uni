# Questions

## What is an almost contact structure?
reduction of structure group to U(n)x 1 (see [Agustin's slides](./papers/Moreno24_slides.pdf))
-> What does that mean?
see Geiges, p. 64, Rmk 2.4.7
almost contact structure is a cooriented hyperplane field eta with a complex bundle structure J and a oriented line-bundle complementary to eta that defines the coorientation
### What is a bundle metric?
Let E -> M a bundle. A bundle metric is a bundle map from the fibre product of E with itself to M x \R
s.t. the reduction to each fibre is a nondegenerate bilinear form.
The fibre product is very similar to the product, only that the product maps need to fit with the two base maps that are given in the fiber product.
Why is the fibre product of something with itself not itself again? Can't I just take the identity map? No, because it needs to commute with both sides.


### What is a principal (G-)bundle?
A fiber bundle with a continuous right G-action s.t. the action preserves fibers and acts transitively and freely.

### What does reduction of structure group mean?
Example: If a manifold is oriented, that corresponds to a reduction of the structure group to GL^+(n,R) because all frames are oriented now.
Analogously, the choice of a volume form corresponds to a reduction of the structure group to SL(n,R).
I think the point is that all transition functions can be written as elements of the smaller group.
For a more formal definition I could look into associated bundles, but I think that might be overkill at this point.


## Why does the definition of weak filling make sense?
What does it mean for a symplectic form to be restricted to a contact structure?
A symplectic form on a mfd associates a skew-symmetric bilinear form to every point of the manifold. The contact structure on the boundary manifold associates a plane to every point. Therefore, at each point we have to consider the restriction of the form to the 2-d subvectorspace of the 4-d tangent space.
