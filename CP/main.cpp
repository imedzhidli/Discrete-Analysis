#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>

using namespace std;

struct Point {
    vector<long double> info;
    size_t index;
    Point() : index(0) {}
    Point(const vector<long double>& dims, size_t idx) : info(dims), index(idx) {}
};

static double Euclidean(const Point &a, const Point &b) {
    double sum = 0;
    for (size_t i = 0; i < a.info.size(); ++i) {
        double diff = a.info[i] - b.info[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

class KDTree{
    struct Node {
    Point point;
    unique_ptr<Node> right = nullptr;
    unique_ptr<Node> left = nullptr;
    Node(const Point& p) : point(p), left(nullptr), right(nullptr) {}
    };
    
    unique_ptr<Node> root = nullptr;
    int dim = 0;

    void build(vector<Point>& points, int l, int r, int depth = 0) {
        if (l > r) return;
        size_t cd = depth % dim;
        int medianIndex = l + (r - l) / 2;
        sort(points.begin() + l, points.begin() + r + 1, [&cd] (Point& a, Point& b) {
        return a.info[cd] < b.info[cd];
        });
        insert(root, 0, points[medianIndex]);
        if (l != r) {
            build(points, l, medianIndex - 1, depth + 1);
            build(points, medianIndex + 1, r, depth + 1);
        }
        return;
    }
    
    void insert(unique_ptr<Node> &node, unsigned int depth, Point &request) {
    if (node == nullptr){
        node = make_unique<Node>(request);
        return;
    }
    unsigned int cur_d = depth % dim;
    if (request.info[cur_d] < node->point.info[cur_d]) {
        insert(node->left, depth + 1, request);
    }
    else {
        insert(node->right, depth + 1, request);
    }
    return;
}

    void nearestNeighborSearch(const unique_ptr<Node>& node, const Point &target, size_t depth, double &bestDist, Point &bestPoint) const {
        if (!node) return;
        double dist = Euclidean(node->point, target);
        size_t axis = depth % dim;
    
        if (dist < bestDist) {
            bestDist = dist;
            bestPoint = node->point;
        }
    
        double diff = target.info[axis] - node->point.info[axis];
        const unique_ptr<Node>& first = (diff < 0) ? node->left : node->right;
        const unique_ptr<Node>& second = (diff >= 0) ? node->left : node->right;
    
        nearestNeighborSearch(first, target, depth + 1, bestDist, bestPoint);
    
        if (fabs(diff) < bestDist) {
            nearestNeighborSearch(second, target, depth + 1, bestDist, bestPoint);
        }
    }
public:
    KDTree(vector<Point> &points, size_t d) : dim(d) {
        build(points, 0, points.size() - 1, 0);
    }

    Point nearestNeighbor(const Point &target) const {
        Point bestPoint;
        double bestDist = numeric_limits<double>::max();
        nearestNeighborSearch(root, target, 0, bestDist, bestPoint);
        return bestPoint;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    size_t n, q; int d;
    cin >> n >> d;
    vector<Point> points;
    points.reserve(n);
    for(size_t i = 0; i < n; ++i){
        vector <long double> dimensions;
        dimensions.resize(d);
        for(size_t j = 0; j < d; ++j){
            cin >> dimensions[j];
        }
        points.emplace_back(dimensions, i);
    }
    KDTree tree(points, d);
    cin >> q;
    for (size_t i = 0; i < q; ++i) {
        vector<long double> queryCoords(d);
        for (size_t j = 0; j < d; ++j) {
            cin >> queryCoords[j];
        }
        Point queryPoint(queryCoords, 0);
        Point nearest = tree.nearestNeighbor(queryPoint);
        cout << nearest.index + 1 << "\n";
    }
    return 0;
}