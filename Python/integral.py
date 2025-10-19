from manim import *

class IntegralAntiderivative(Scene):
    def construct(self):
        # Set up axes
        axes = Axes(
            x_range=[0, 5],
            y_range=[0, 8],
            axis_config={"color": BLUE},
        )
        axes_labels = axes.get_axis_labels()

        # Define the function and its integral
        def f(x):
            return 0.2 * (x - 2)**2 + 1
        
        def F(x):
            return 0.2/3 * (x - 2)**3 + x - 0.2/3*(-2)**3 - 2

        # Create the curve
        graph = axes.plot(f, color=GREEN)
        graph_label = axes.get_graph_label(graph, label="f(x)")

        # Initial setup
        self.play(Create(axes), Write(axes_labels))
        self.play(Create(graph), Write(graph_label))
        self.wait(1)

        # Area visualization
        x_tracker = ValueTracker(1)
        area = always_redraw(lambda: axes.get_area(graph, x_range=[1, x_tracker.get_value()]))
        area_label = Text("Area = F(x)").next_to(axes, UP).shift(RIGHT*2)

        vertical_line = always_redraw(lambda: DashedLine(
            start=axes.c2p(x_tracker.get_value(), 0),
            end=axes.c2p(x_tracker.get_value(), f(x_tracker.get_value())),
            color=YELLOW
        ))

        self.play(
            Create(vertical_line),
            FadeIn(area),
            Write(area_label)
        )
        self.wait(1)

        # Animate the area growing
        self.play(x_tracker.animate.set_value(4), run_time=3)
        self.wait(1)

        # Show small change in x
        h = 0.5
        dx_line = Line(
            start=axes.c2p(x_tracker.get_value(), 0),
            end=axes.c2p(x_tracker.get_value() + h, 0),
            color=RED,
            stroke_width=5
        )
        dx_label = Text("h").next_to(dx_line, DOWN)

        area_diff = axes.get_area(graph, x_range=[
            x_tracker.get_value(), 
            x_tracker.get_value() + h
        ], color=RED)

        self.play(
            Create(dx_line), 
            Write(dx_label),
            FadeIn(area_diff)
        )
        self.wait(1)

        # Show the rate of change
        approx_rect = Rectangle(
            width=h,
            height=f(x_tracker.get_value()),
            color=RED,
            fill_opacity=0.5,
            stroke_width=0
        ).move_to(axes.c2p(
            x_tracker.get_value() + h/2, 
            f(x_tracker.get_value())/2
        ))

        rate_text = MathTex(r"\frac{F(x+h) - F(x)}{h} \approx f(x)").to_edge(UP)
        self.play(
            Transform(area_diff, approx_rect),
            Write(rate_text)
        )
        self.wait(2)

        # Show limit process
        limit_text = MathTex(r"\lim_{h \to 0} \frac{F(x+h) - F(x)}{h} = f(x)").to_edge(UP)
        self.play(
            Transform(rate_text, limit_text),
            dx_line.animate.set_width(0.1, stretch=True),
            dx_label.animate.next_to(dx_line, DOWN, buff=0.1),
            run_time=2
        )
        self.wait(2)

        # Show derivative relationship
        derivative_text = MathTex(r"F'(x) = f(x)").scale(1.5).to_edge(UP)
        self.play(
            Transform(rate_text, derivative_text),
            FadeOut(dx_line),
            FadeOut(dx_label),
            FadeOut(area_diff)
        )
        self.wait(2)

        # Show antiderivative connection
        final_text = Text("The integral accumulates area\nwhile the derivative measures rate of change\nThey are inverse operations!", 
                        t2c={"integral": YELLOW, "derivative": GREEN}).scale(0.8).to_edge(DOWN)
        self.play(Write(final_text))
        self.wait(3)