## Argo CD Installation
To install Argo CD in your Kubernetes cluster using Helm, follow these steps:
```bash
bash k8s/argocd_installation.sh
```

### get initial admin password
```bash
kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}"
```

### port-forwarding argocd-server service
```bash
kubectl port-forward svc/argocd-server -n argocd 8000:443
```