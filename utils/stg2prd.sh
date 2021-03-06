git checkout prd

echo "======================"
echo "Merging stg branch"
echo "======================"

git merge stg

timestamp=$(date +"%m_%d_%Y__%H_%M")
echo "======================"
echo "Tagging as ${timestamp}"
echo "======================"
git tag -a "$timestamp" -m "stg2prd"

echo "======================"
echo "Pushing commits and tags"
echo "======================"
git push --set-upstream origin prd
git push --tags

echo "======================"
echo "Checking out develop branch"
echo "======================"
git checkout dev
git push
