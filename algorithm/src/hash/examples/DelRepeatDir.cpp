// problem link: https://leetcode.cn/problems/delete-duplicate-folders-in-system/

// This is a VERY important problem that teaches you how to use Hash Function
// on a Tree!! Additionally, it is also a good example of how to use Trie.
#include <bits/stdc++.h>
#include <unordered_map>
#include <map>
using namespace std;
class TrieNode {
public:
    string name;
    // 定义成map是十分重要的，详见下文。
    map<string, TrieNode*> children;
    bool deleted = false;
    TrieNode(string name = "") : name(name) {}
};

class Solution {
public:
    unordered_map<string, vector<TrieNode*>> duplicates;

    void insert(TrieNode* root, const vector<string>& path) {
        for (const auto& name : path) {
            if (!root->children.count(name)) {
                root->children[name] = new TrieNode(name);
            }
            root = root->children[name];
        }
    }

    string serialize(TrieNode* node) {
        if (node->children.empty()) return node->name;

        // 如果在TrieNode中定义成unordered_map，那么同样的子树结构，其在
        // 父节点出现的顺序可能不一样，从而导致错误。所以，必须要在此处进行排序。
        // vector<pair<string, string>> sortedChildren;
        // for (auto& child : node->children) {
        //     string childSer = serialize(child.second);
        //     sortedChildren.push_back({child.first, childSer});
        // }
        // sort(sortedChildren.begin(), sortedChildren.end());

        // string curSer;
        // for (auto& [name, ser] : sortedChildren) {
        //     curSer += "(" + ser + ")";
        // }

        string curSer = "";
        for(auto& child: node->children){
            curSer += "(" + serialize(child.second) + ")";
        }

        duplicates[curSer].push_back(node);
        return curSer + node->name;
    }

    void markDuplicates() {
        for (auto& [ser, nodes] : duplicates) {
            if (nodes.size() > 1) {
                for (auto* node : nodes) node->deleted = true;
            }
        }
    }

    void collectPaths(TrieNode* node, vector<string>& path, vector<vector<string>>& result) {
        for (auto& [name, child] : node->children) {
            if (child->deleted) continue;
            path.push_back(name);
            result.push_back(path);
            collectPaths(child, path, result);
            path.pop_back();
        }
    }

    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        TrieNode* root = new TrieNode();
        for (auto& path : paths) insert(root, path);
        serialize(root);
        markDuplicates();

        vector<vector<string>> result;
        vector<string> path;
        collectPaths(root, path, result);
        return result;
    }
};