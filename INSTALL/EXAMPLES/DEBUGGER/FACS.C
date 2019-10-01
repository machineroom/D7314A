/***************************************
*
*  Debugger example:  facs.c
*
*  idebug (and parallel C) example based on similar program 
*  in occam toolset.
*
*  Uses 5 processes to compute the sum of the squares of the
*  first N factorials using a rather inefficient algorithm.
*
*  Plumbing:
*
*   - > feed -> facs -> square -> sum -> control <--> User I/O
*  |                                        |
*   ----------------------------------------
*
***************************************/


#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <channel.h>


const double	stop_real    = -1.0;
const int	stop_integer = -1;


/*  output a double down a channel  */
void
ChanOutDouble (Channel *out, double value)

{
	ChanOut (out, (void *) &value, sizeof (value));
}


/*  input a double from a channel  */
double
ChanInDouble (Channel *in)

{
	double	value;

	ChanIn (in, (void *) &value, sizeof (value));
	return value;
}


/*  compute factorial  */
double
factorial (int n)

{
	double	result;
	int	i;

	result = 1.0;
	for (i = 1; i <= n; ++i)   {
		result = result * i;
	}
	return result;
}


/*  source stream of ints  */
void
feed (Process *p, Channel *in, Channel *out)

{
	int	n, i;

	(void) p;	/*  stop compiler usage warning  */

	n = ChanInInt (in);
	for (i = 0; i < n; ++i)   {
		ChanOutInt (out, i);
	}
	ChanOutInt (out, stop_integer);
}


/*  generate stream of factorials  */
void
facs (Process *p, Channel *in, Channel *out)

{
	int	x;
	double	fac;

	(void) p;	/*  stop compiler usage warning  */

	x = ChanInInt (in);
	while (x != stop_integer)   {
		fac = factorial (x);
		ChanOutDouble (out, fac);
		x = ChanInInt (in);
	}
	ChanOutDouble (out, stop_real);
}


/*  generate stream of squares  */
void
square (Process *p, Channel *in, Channel *out)

{
	double	x, sq;

	(void) p;	/*  stop compiler usage warning  */

	x = ChanInDouble (in);
	while (x != stop_real)   {
		sq = x * x;
		ChanOutDouble (out, sq);
		x = ChanInDouble (in);
	}
	ChanOutDouble (out, stop_real);
}


/*  sum input  */
void
sum (Process *p, Channel *in, Channel *out)

{
	double	total, x;

	(void) p;	/*  stop compiler usage warning  */

	total = 0.0;
	x = ChanInDouble (in);
	while (x != stop_real)   {
		total = total + x;
		x = ChanInDouble (in);
	}
	ChanOutDouble (out, total);
}


/*  user interface and control  */
void
control (Process *p, Channel *in, Channel *out)

{
	double	value;
	int	n;

	(void) p;	/*  stop compiler usage warning  */

	printf ("Sum of the first n squares of factorials\n");
	do   {
		printf ("Please type n : ");
	}   while (scanf ("%d", &n) != 1);
	printf ("n = %d\n", n);
	printf ("Calculating factorials ... ");

	ChanOutInt (out, n);
	value = ChanInDouble (in);

	printf ("\nThe result was : %g\n", value);
}


Channel *
Checked_ChanAlloc ()

{
	Channel	*chan;

	if ((chan = ChanAlloc ()) == NULL)   {
		fprintf (stderr, "ChanAlloc () failed\n");
		exit (EXIT_FAILURE);
	}
	return chan;
}


Process *
Checked_ProcAlloc (void (*func)(), int sp, int nparam,
		   Channel *c1, Channel *c2)

{
	Process	*proc;

	proc = ProcAlloc (func, sp, nparam, c1, c2);
	if (proc == NULL)   {
		fprintf (stderr, "ProcAlloc () failed\n");
		exit (EXIT_FAILURE);
	}
	return proc;
}


int
main (void)

{
	Channel	*facs_to_square, *square_to_sum;
	Channel *sum_to_control, *feed_to_facs;
	Channel *control_to_feed;

	Process *p_feed, *p_facs, *p_square;
	Process *p_sum, *p_control;

	facs_to_square	= Checked_ChanAlloc ();
	square_to_sum	= Checked_ChanAlloc ();
	sum_to_control	= Checked_ChanAlloc ();
	feed_to_facs	= Checked_ChanAlloc ();
	control_to_feed	= Checked_ChanAlloc ();

	p_feed = Checked_ProcAlloc (feed, 0, 2,
			control_to_feed, feed_to_facs);
	p_facs = Checked_ProcAlloc (facs, 0, 2,
			feed_to_facs, facs_to_square);
	p_square = Checked_ProcAlloc (square, 0, 2,
			facs_to_square, square_to_sum);
	p_sum = Checked_ProcAlloc (sum, 0, 2,
			square_to_sum, sum_to_control);
	p_control = Checked_ProcAlloc (control, 0, 2,
			sum_to_control, control_to_feed);

	ProcPar (p_feed, p_facs, p_square, p_sum,
					p_control, NULL);

	exit (EXIT_SUCCESS);
}
