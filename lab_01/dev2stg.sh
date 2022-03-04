git checkout stg
echo "Merging develop branch"
git merge dev

timestamp=$(date +%s)
echo "Tagging as ${timestamp}"
git tag -a "$timestamp" -m "dev2stg"

echo "Pushing commits and tags"
git push --set-upstream origin stg
git push --tags

echo "Checking out develop branch"
git checkout dev
git push
