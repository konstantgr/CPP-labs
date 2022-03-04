git checkout stg

echo "======================"
echo "Merging develop branch"
echo "======================"

git merge dev

timestamp=$(date +"%m_%d_%Y__%H_%M")
echo "======================"
echo "Tagging as ${timestamp}"
echo "======================"
git tag -a "$timestamp" -m "dev2stg"

echo "======================"
echo "Pushing commits and tags"
echo "======================"
git push --set-upstream origin stg
git push --tags

echo "======================"
echo "Checking out develop branch"
echo "======================"
git checkout dev
git push
