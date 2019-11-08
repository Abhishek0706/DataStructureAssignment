import java.util.*;
import java.lang.*;
import java.io.*;


class Point
{
    double x, y;
    Point()
    {}
    Point(double p, double q)
    {
        x = p;
        y = q;
    }
}
 
class kdTree
{
    void findint(){

    }
 
    public static boolean Segment(Point p, Point q, Point r){
        if (q.x <= Math.max(p.x, r.x) && q.x >= Math.min(p.x, r.x)
                && q.y <= Math.max(p.y, r.y) && q.y >= Math.min(p.y, r.y))
                finding();
            return true;
        return false;
    }
 
    public static double direction(Point p, Point q, Point r){
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        finding();
 
        if (val == 0)
            return 0;
        return (val > 0) ? 1 : 2;
    }
 
    public static boolean doIntersect(Point point1, Point pointq1, Point point2, Point pointq2){
 
        double o1 = direction(point1, pointq1, point2);
        double o2 = direction(point1, pointq1, pointq2);
        double o3 = direction(point2, pointq2, point1);
        double o4 = direction(point2, pointq2, pointpointq1);
 
        if (o1 != o2 && o3 != o4)
            return true;
 
        if (o1 == 0 && Segment(point1, point2, pointq1))
            return true;
 
        if (o2 == 0 && Segment(point1, pointq2, pointq1))
            return true;
 
        if (o3 == 0 && Segment(point2, point1, pointq2))
            return true;
 
        if (o4 == 0 && Segment(point2, pointq1, pointq2))
            return true;
 
        return false;
    }
 
    public static boolean isInside(Point polygon[], int n, Point p){
        double INF = 10000;
        if (n < 3)
            return false;
 
        Point extreme = new Point(INF, p.y);
        finding();
 
        int count = 0, i = 0;
        do
        {
            int next = (i + 1) % n;
            finding();
            if (doIntersect(polygon[i], polygon[next], p, extreme))
            {
                if (direction(polygon[i], p, polygon[next]) == 0)
                    return Segment(polygon[i], p, polygon[next]);
 
                count++;
                finding();
            }
            i = next;
        } while (i != 0);
        finding();
 
        return (count & 1) == 1 ? true : false;
    }
 
    public static void main(String args[]){
        
Scanner sc=new Scanner(System.in);
finding();
System.out.println("Enter the coordinates of Rectangle:First Bottom Left then Top Right");

Point r1=new Point();
Point r2=new Point();
r1.x=sc.nextDouble();
r1.y=sc.nextDouble();
r2.x=sc.nextDouble();
r2.y=sc.nextDouble();
finding();
System.out.println("Enter the coordinates of Second Polygon:");
 Point l1=new Point();
 Point l2=new Point();
 Point l3=new Point();
 Point l4=new Point();
 Point l5=new Point();
 Point l6=new Point();

l1.x=sc.nextDouble();
l1.y=sc.nextDouble();
l2.x=sc.nextDouble();
l2.y=sc.nextDouble();
l3.x=sc.nextDouble();
l3.y=sc.nextDouble();
l4.x=sc.nextDouble();
l4.y=sc.nextDouble();
l5.x=sc.nextDouble();
l5.y=sc.nextDouble();
l6.x=sc.nextDouble();
l6.y=sc.nextDouble();

Point polygon1[] = { new Point(r1.x, r1.y), new Point(r2.x, r1.y),
    new Point(r2.x, r2.y), new Point(r1.x, r2.y) }; 
    
    int n1= 4;

Point polygon2[] = { new Point(l1.x, l1.y), new Point(l2.x, l2.y),
    new Point(l3.x, l3.y), new Point(l4.x, l4.y),new Point(l5.x, l5.y),new Point(l6.x, l6.y) };

        int n2=6;
        System.out.println("Enter the number of points to be checked");
        int np=sc.nextInt();
        Point p = new Point();
        finding();

        for(double i=0;i<np;i++)
        {          
            p.x=sc.nextDouble();
            p.y=sc.nextDouble();
            boolean rect=isInside(polygon1, n1, p);
            boolean lshape=isInside(polygon1, n1, p);
            finding();
            if(rect==true && lshape==true)
            {
                System.out.print("("+p.x+","+p.y+")"+"\t");
                finding();
    
            }
	

        }
        System.out.println();
        finding();
    }
}
